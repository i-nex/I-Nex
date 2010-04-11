#!/usr/bin/python
# Written by Stephane Graber <stgraber@stgraber.org>
#            Daniel Bartlett <dan@f-box.org>
# Last modification : Mon Jan 28 22:33:23 CET 2008

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

try:
    import urllib, os, sys, re, getopt, xml.dom.minidom, gettext
    from gettext import gettext as _
    import configobj

    gettext.textdomain("pastebinit")

    defaultPB = "http://pastebin.com" #Default pastebin
    version = "1.1" #Version number to show in the usage
    configfile = os.path.expanduser("~/.pastebinit.xml")

    # Custom urlopener to handle 401's
    class pasteURLopener(urllib.FancyURLopener):
        def http_error_401(self, url, fp, errcode, errmsg, headers, data=None):
            return None

    def preloadPastebins():
        # Check several places for config files:
        #  - global config in /etc/pastebin.d
        #  - for source checkout, config in the checkout
        #  - user's overrides in ~/.pastebin.d
        # Files found later override files found earlier.
        for confdir in ['/etc/pastebin.d',
                        os.path.join(os.path.dirname(__file__), 'pastebin.d'),
                        os.path.expanduser('~/.pastebin.d')]:
            try:
                confdirlist = os.listdir(confdir)
            except OSError:
                continue
            pastebind = {}
            for fileitem in confdirlist:
                if fileitem.startswith('.'):
                    continue
                filename = os.path.join(confdir, fileitem)
                try:
                    bininstance = configobj.ConfigObj(filename)
                except configobj.ConfigObjError, e:
                    print >> sys.stderr, '%s: %s' % (filename, e)
                    continue
                try:
                    section = bininstance['pastebin']
                except KeyError:
                    print >> sys.stderr, _('%s: no section [pastebin]') % filename
                    continue
                try:
                    basename = section['basename']
                except KeyError:
                    print >> sys.stderr, _("%s: no 'basename' in [pastebin]") % filename
                    continue
                pastebind[basename] = bininstance
            return pastebind

    # pastey.net obfuscates parent ids for replies.  Rather than taking the
    # post ID given as the parent ID, we must handle this by going to that
    # post page and looking up what the invisible parent ID field will be
    # set to for children.
    def doParentFixup(website, paramname, parentid):
        if parentid == "":
            return ""
        url_opener = pasteURLopener()
        page = url_opener.open(website + '/' + parentid, None)
        matches = re.split('<input.*?name="' + paramname + '".*?value="(.*?)"', page.read())
        if len(matches) <= 1 or re.match(parentid, matches[1]) == None:
            # The obfuscated version didn't begin with the partial version,
            # or unable to find the obfuscated version for some reason!
            # Create a paste with no parent (should we throw, instead?)
            return ""
        return matches[1]

    #Return the parameters depending of the pastebin used
    def getParameters(website, pastebind, content, user, jabberid, version, format, parentpid, permatag, title, username, password):
        "Return the parameters array for the selected pastebin"
        params = {}
        for pastebin in pastebind:
            if re.search(pastebind[pastebin]['pastebin']['regexp'], website):
                for param in pastebind[pastebin]['format'].keys():
                    paramname = pastebind[pastebin]['format'][param]
                    if param == 'user':
                        params[paramname] = user
                    elif param == 'content':
                        params[paramname] = content
                    elif param == 'title':
                        params[paramname] = title
                    elif param == 'version':
                        params[paramname] = version
                    elif param == 'format':
                        params[paramname] = format
                    elif param == 'parentpid':
                        params[paramname] = doParentFixup(website, paramname, parentpid)
                    elif param == 'permatag':
                        params[paramname] = permatag
                    elif param == 'username':
                        params[paramname] = username
                    elif param == 'password':
                        params[paramname] = password
                    elif param == 'jabberid':
                        params[paramname] = jabberid
                    else:
                        params[paramname] = pastebind[pastebin]['defaults'][param]
        if params:
            return params
        else:
            sys.exit(_("Unknown website, please post a bugreport to request this pastebin to be added (%s)") % website)

    #XML Handling methods
    def getText(nodelist):
        rc = ""
        for node in nodelist:
            if node.nodeType == node.TEXT_NODE:
                rc = rc + node.data
        return rc.encode('utf-8')

    def getNodes(nodes, title):
        return nodes.getElementsByTagName(title)

    def getFirstNode(nodes, title):
        return getNodes(nodes, title)[0]

    def getFirstNodeText(nodes, title):
        return getText(getFirstNode(nodes, title).childNodes)

    # Display usage instructions
    def Usage():
        print "pastebinit v" + version
        print "Reads on stdin for input or takes a filename as first parameter"
        print _("Optional arguments:")
        print _("\t-h This help screen")
        print _("\t-b <pastebin url:default is '%s'>") % website
        print _("\t-a <author:default is '%s'>") % user
        print _("\t-f <format of paste:default is '%s'>") % format
        print _("\t-r <parent posts ID:defaults to none>")
#        print _("Optional arguments supported only by 1t2.us:")
#        print _("\t-j <jabberid for notifications:default is '%s'>") % jabberid
#        print _("\t-m <permatag for all versions of a post:default is blank>")
#        print _("\t-t <title of paste:default is blank>")
#        print _("\t-u <username> -p <password>")

    # Set defaults
    website = defaultPB
    user = os.environ.get('USER')
    jabberid = ""
    title = ""
    permatag = ""
    format = "text"
    username = ""
    password = ""
    filename = ""
    content = ""
    parentpid = ""

    #Example configuration file string
    configexample = """\
<pastebinit>
<pastebin>http://paste.debian.net</pastebin>
<author>A pastebinit user</author>
<jabberid>nobody@nowhere.org</jabberid>
<format>text</format>
</pastebinit>
"""

    #Open configuration file if it exists
    try:
        f = open(configfile)
        configtext = f.read()
        f.close()
        gotconfigxml = True
    except KeyboardInterrupt:
        sys.exit(_("KeyboardInterrupt caught."))
    except:
        gotconfigxml = False

    #Parse configuration file
    if gotconfigxml:
        try:
            configxml = xml.dom.minidom.parseString(configtext)
            website = getFirstNodeText(configxml, "pastebin")
            user = getFirstNodeText(configxml, "author")
            format = getFirstNodeText(configxml, "format")
            jabberid = getFirstNodeText(configxml, "jabberid")
        except KeyboardInterrupt:
            sys.exit(_("KeyboardInterrupt caught."))
        except:
            raise
            print _("Error parsing configuration file!")
            print _("Please ensure that your configuration file looks similar to the following:")
            print configexample
            sys.exit(1)

    # Get options
    try:
        optlist, list = getopt.getopt(sys.argv[1:], 'hi:f:b:a:r:j:t:m:u:p:')
    except KeyboardInterrupt:
        sys.exit(_("KeyboardInterrupt caught."))
    except getopt.GetoptError:
        print _("Invalid arguments!\n")
        Usage()
        sys.exit(1)

    # Iterate through options
    for opt in optlist:
        if opt[0] == "-h":
            Usage()
            sys.exit(1)
        if opt[0] == "-i":
            filename = opt[1]
        elif opt[0] == "-f":
            format = opt[1]
        elif opt[0] == "-b":
            website = opt[1]
        elif opt[0] == "-a":
            user = opt[1]
        elif opt[0] == "-r":
            parentpid = opt[1]
        elif opt[0] == "-j":
            jabberid = opt[1]
        elif opt[0] == "-t":
            title = opt[1]
        elif opt[0] == "-m":
            permatag = opt[1]
        elif opt[0] == "-u":
            username = opt[1]
        elif opt[0] == "-p":
            password = opt[1]

    if filename == "" and len(list) >= 1:
        filename = list[0]

    #If - is specified as a filename read from stdin, otherwise load the specified file.
    if (filename == "" or filename == "-") and content == "":
        content = sys.stdin.read()
    elif content == "":
        try:
            f = open(filename)
            content = f.read()
            f.close()
        except KeyboardInterrupt:
            sys.exit(_("KeyboardInterrupt caught."))
        except:
            sys.exit(_("Unable to read from: %s") % filename)
    if not content:
        sys.exit(_("You are trying to send an empty document, exiting.")) 
    pastebind = preloadPastebins() #get the config from /etc/pastebin.d/
    params = getParameters(website, pastebind, content, user, jabberid, version, format, parentpid, permatag, title, username, password) #Get the parameters array

    if not website.endswith("/"):
        website += "/"

    reLink = None
    tmp_page = ""
    if "page" in params:
        website += params['page']
        tmp_page = params['page']
        del params["page"]
    if "regexp" in params:
        reLink = params['regexp']
        del params["regexp"]
    params = urllib.urlencode(params) #Convert to a format usable with the HTML POST

    url_opener = pasteURLopener()
    page = url_opener.open(website, params) #Send the informations and be redirected to the final page

    try:
        if reLink: #Check if we have to apply a regexp
            website = website.replace(tmp_page, "")
            if reLink == '(.*)':
                print page.read().strip()
            else:
                print website + re.split(reLink, page.read())[1] #Print the result of the Regexp
        else:
            print page.url #Get the final page and show the ur
    except KeyboardInterrupt:
        sys.exit(_("KeyboardInterrupt caught."))
    except:
        raise
        sys.exit(_("Unable to read or parse the result page, it could be a server timeout or a change server side, try with another pastebin."))

except KeyboardInterrupt:
    sys.exit(_("KeyboardInterrupt caught."))
