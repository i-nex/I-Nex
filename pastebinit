#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Author: Stéphane Graber <stgraber@ubuntu.com>
# Written by Stéphane Graber <stgraber@stgraber.org>
#            Daniel Bartlett <dan@f-box.org>
# Last modification : Mon Jan  6 18:46:46 EST 2014

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

from __future__ import print_function

import sys
if sys.version[0] == "2":
    from ConfigParser import NoOptionError
    from ConfigParser import SafeConfigParser as ConfigParser
    from urllib import urlencode
    from urllib import FancyURLopener
else:
    from configparser import ConfigParser, NoOptionError
    from urllib.parse import urlencode
    from urllib.request import FancyURLopener

# Set the default pastebin
defaultPB = "pastebin.com"

# Now try to override it with a distributor pastebin
try:
    import platform
    release = platform.linux_distribution()[0].lower()
    if release == 'debian':
        defaultPB = "paste.debian.net"
    elif release == 'fedora':
        defaultPB = "fpaste.org"
    elif release == 'ubuntu':
        defaultPB = "paste.ubuntu.com"
except ImportError:
    pass

try:
    import getopt
    import gettext
    import os
    import re
    import socket
    import xml.dom.minidom

    try:
        import json
    except ImportError:
        json = None

    _ = gettext.gettext
    gettext.textdomain("pastebinit")

    # Timeout after 5s
    socket.setdefaulttimeout(15)

    # Version number to show in the usage
    version = "1.5"
    configfile = os.path.expanduser("~/.pastebinit.xml")

    # Custom urlopener to handle 401's
    class pasteURLopener(FancyURLopener):
        version = "Pastebinit v%s" % version

        def http_error_401(self, url, fp, errcode, errmsg, headers, data=None):
            return None

    def preloadPastebins():
        # Check several places for config files:
        #  - global config in /etc/pastebin.d
        #  - for source checkout, config in the checkout
        #  - user's overrides in ~/.pastebin.d
        # Files found later override files found earlier.
        pastebind = {}
        for confdir in ['/usr/share/pastebin.d', '/etc/pastebin.d',
                        '/usr/local/etc/pastebin.d',
                        os.path.expanduser('~/.pastebin.d'),
                        os.path.join(
                            os.path.dirname(
                                os.path.realpath(__file__)), 'pastebin.d')]:
            try:
                confdirlist = os.listdir(confdir)
            except OSError:
                continue

            for fileitem in confdirlist:
                if fileitem.startswith('.') or not fileitem.endswith('.conf'):
                    continue

                filename = os.path.join(confdir, fileitem)
                instance = ConfigParser()
                try:
                    instance.read(filename)
                except UnicodeError:
                    continue

                if not instance.has_section('pastebin'):
                    print(_('%s: no section [pastebin]') % filename,
                          file=sys.stderr)
                    continue

                if not instance.has_option('pastebin', 'basename'):
                    print(_("%s: no 'basename' in [pastebin]") % filename,
                          file=sys.stderr)
                    continue

                pastebind[instance.get('pastebin', 'basename')] = instance
        return pastebind

    # Return the parameters depending of the pastebin used
    def getParameters(website, pastebind, content, user, jabberid, version,
                      format, permatag, title, username,
                      password, private):
        "Return the parameters array for the selected pastebin"
        params = {}
        for paste_name, paste_config in pastebind.items():
            basename = paste_config.get('pastebin', 'basename')
            try:
                https = paste_config.get('pastebin', 'https')
            except:
                https = False

            if basename == website or paste_name == website:
                if https:
                    website = "https://%s" % basename
                else:
                    website = "http://%s" % basename

            if re.search(paste_config.get('pastebin', 'regexp'), website):
                if paste_config.has_option('pastebin', 'sizelimit'):
                    params['sizelimit'] = paste_config.get('pastebin',
                                                           'sizelimit')

                for param in paste_config.options('format'):
                    paramname = paste_config.get('format', param)
                    if param == 'user':
                        params[paramname] = user
                    elif param == 'content':
                        params[paramname] = content
                    elif param == 'title':
                        params[paramname] = title
                    elif param == 'version':
                        params[paramname] = version
                    elif param == 'format':
                        try:
                            params[paramname] = paste_config.get('defaults',
                                                                 'format')
                        except NoOptionError:
                            params[paramname] = format
                    elif param == 'permatag':
                        params[paramname] = permatag
                    elif param == 'private':
                        params[paramname] = private
                    elif param == 'username':
                        params[paramname] = username
                    elif param == 'password':
                        params[paramname] = password
                    elif param == 'jabberid':
                        params[paramname] = jabberid
                    else:
                        params[paramname] = paste_config.get('defaults', param)
        if params:
            return website, params
        else:
            print(_("Unknown website, please post a bugreport to request "
                    "this pastebin to be added (%s)") % website,
                  file=sys.stderr)
            sys.exit(1)

    # XML Handling methods
    def getText(nodelist):
        rc = ""
        for node in nodelist:
            if node.nodeType == node.TEXT_NODE:
                rc = rc + node.data
        return rc

    def getNodes(nodes, title):
        return nodes.getElementsByTagName(title)

    def getFirstNode(nodes, title):
        return getNodes(nodes, title)[0]

    def getFirstNodeText(nodes, title):
        return getText(getFirstNode(nodes, title).childNodes)

    # Display usage instructions
    def Usage(fd=sys.stdout):
        print("pastebinit v" + version, file=fd)
        print(_("Reads on stdin for input or takes a list of filenames "
                "as parameters"), file=fd)
        print(_("\t-E also print content to standard output"), file=fd)
        print(_("Optional arguments (not supported by all pastebins):"),
              file=fd)
        print(_("\t-a <author:default is '%s'>") % user, file=fd)
        print(_("\t-b <pastebin url:default is '%s'>") % website, file=fd)
        print(_("\t-f <format of paste:default is '%s' (or from pastebin config)>") % format, file=fd)  # noqa
        print(_("\t-h This help screen"), file=fd)
        print(_("\t-i <input file>"), file=fd)
        print(_("\t-l List all supported pastebins"), file=fd)
        print(_("\t-j <jabberid for notifications:default is '%s'>") %
              jabberid, file=fd)
        print(_("\t-m <permatag for all versions of a post:default is blank>"),
              file=fd)
        print(_("\t-t <title of paste:default is blank>"), file=fd)
        print(_("\t-P Private. Makes your paste hidden if possible"), file=fd)
        print(_("\t-u <username> -p <password>"), file=fd)
        print(_("\t-v Print the version number"), file=fd)
        print(_("\t--verbose Verbose output to stderr"), file=fd)

    # Set defaults
    website = defaultPB
    user = os.environ.get('USER', os.environ.get('LOGNAME'))
    jabberid = ""
    title = ""
    permatag = ""
    format = "text"
    username = ""
    password = ""
    filenames = []
    content = ""
    private = 0
    verbose = False
    echo = False

    # Example configuration file string
    configexample = """\
<pastebinit>
<pastebin>paste.debian.net</pastebin>
<author>A pastebinit user</author>
<jabberid>nobody@nowhere.org</jabberid>
<format>text</format>
</pastebinit>
"""

    # Open configuration file if it exists
    try:
        f = open(configfile)
        configtext = f.read()
        f.close()
        gotconfigxml = True
    except KeyboardInterrupt:
        print(_("KeyboardInterrupt caught."), file=sys.stderr)
        sys.exit(1)
    except:
        gotconfigxml = False

    # Parse configuration file
    if gotconfigxml:
        try:
            configxml = xml.dom.minidom.parseString(configtext)
            for variable, key in (('pastebin', 'website'), ('author', 'user'),
                                  ('format', 'format'),
                                  ('jabberid', 'jabberid')):
                try:
                    value = getFirstNodeText(configxml, variable)
                    vars()[key] = value
                except:
                    pass
        except KeyboardInterrupt:
            print(_("KeyboardInterrupt caught."), file=sys.stderr)
            sys.exit(1)
        except:
            print(_("Error parsing configuration file!"), file=sys.stderr)
            print(_("Please ensure that your configuration file looks "
                    "similar to the following:"), file=sys.stderr)
            print(configexample, file=sys.stderr)
            sys.exit(1)

    # Get options
    try:
        optlist, arglist = getopt.getopt(sys.argv[1:],
                                         'EPhvli:f:b:a:j:t:m:u:p:',
                                         ('verbose',))
    except KeyboardInterrupt:
        print(_("KeyboardInterrupt caught."), file=sys.stderr)
        sys.exit(1)
    except getopt.GetoptError as e:
        print(_("Invalid arguments: %s!" % e)+"\n", file=sys.stderr)
        Usage(sys.stderr)
        sys.exit(1)

    # Get the config
    pastebind = preloadPastebins()

    # Iterate through options
    for opt in optlist:
        if opt[0] == "-h":
            Usage()
            sys.exit(0)
        if opt[0] == "-i":
            filenames.append(opt[1])
        elif opt[0] == "-E":
            echo = True
        elif opt[0] == "-f":
            format = opt[1]
        elif opt[0] == "-b":
            website = opt[1]
        elif opt[0] == "-a":
            user = opt[1]
        elif opt[0] == "-j":
            jabberid = opt[1]
        elif opt[0] == "-l":
            print(_("Supported pastebins:"))
            for pastebin in sorted(pastebind):
                print("- %s" % pastebin)
            sys.exit(0)
        elif opt[0] == "-t":
            title = opt[1]
        elif opt[0] == "-m":
            permatag = opt[1]
        elif opt[0] == "-P":
            private = 1
        elif opt[0] == "-u":
            username = opt[1]
        elif opt[0] == "-p":
            password = opt[1]
        elif opt[0] == "-v":
            print("pastebinit v" + version)
            sys.exit(0)
        elif opt[0] == "--verbose":
            verbose = True

    filenames += arglist

    if not filenames:
        filenames.append("-")

    contents = []
    for filename in filenames:
        # If - is specified as a filename read from stdin
        # otherwise load the specified files.
        if filename == "-":
            content = sys.stdin.read()
        else:
            try:
                with open(filename, "rb") as fd:
                    content = fd.read()
            except KeyboardInterrupt:
                print(_("KeyboardInterrupt caught."), file=sys.stderr)
                sys.exit(1)
            except:
                print(_("Unable to read from: %s") % filename, file=sys.stderr)
                sys.exit(1)

        if not content:
            print(_("You are trying to send an empty document, exiting."),
                  file=sys.stderr)
            sys.exit(1)

        contents.append(content)
        if echo:
            print(content)

    for content in contents:
        # Get the parameter array
        website, params = getParameters(website, pastebind, content, user,
                                        jabberid, version, format,
                                        permatag, title, username, password,
                                        private)

        if not website.endswith("/"):
            website += "/"

        if "sizelimit" in params:
            if len(content) > int(params['sizelimit']):
                print(_("The content you are trying to send exceeds "
                        "the pastebin's size limit."), file=sys.stderr)
                sys.exit(1)
            else:
                del params['sizelimit']

        if "page" in params:
            # Use page, without leading slash: website has a trailing one.
            fetch_url = website + params['page'].lstrip("/")
            del params['page']
        else:
            fetch_url = website
        if "regexp" in params:
            reLink = params['regexp']
            del params["regexp"]
        else:
            reLink = False
        # Get target_url for replacement, only used with reLink.
        if "target_url" in params:
            relink_target_url = params["target_url"]
            del params["target_url"]
            if not reLink:
                print("Warning: using target_url without regexp.",
                      file=sys.stderr)
        elif reLink:
            relink_target_url = website
        if 'post_format' in params:
            post_format = params['post_format']
            del params['post_format']
        else:
            post_format = 'standard'

        url_opener = pasteURLopener()

        if post_format == 'json':
            if json:
                params = json.dumps(params)
                url_opener.addheader('Content-type', 'text/json')
            else:
                print(_("Could not find any json library."), file=sys.stderr)
                sys.exit(1)
        else:
            # Convert to a format usable with the HTML POST
            params = urlencode(params)

        # Send the informations and be redirected to the final page
        if verbose:
            print("POSTing to: %s\nParams: %s" % (
                fetch_url, str(params)), file=sys.stderr)
        try:
            page = url_opener.open(fetch_url, params)
        except Exception as e:
            print(_("Failed to contact the server: %s") % e, file=sys.stderr)
            sys.exit(1)

        try:
            # Check if we have to apply a regexp
            page_url = ""
            if reLink:
                if reLink == '(.*)':
                    page_url = page.read().decode('utf-8').strip()
                else:
                    # Print the result of the regexp
                    page_url = relink_target_url + re.split(
                        reLink,
                        page.read().decode('utf-8'))[1]
            else:
                # Get the final page and show the url
                if echo:
                    print("-" * len(page.url))
                page_url = page.url

            print(page_url.strip())
        except KeyboardInterrupt:
            print(_("KeyboardInterrupt caught."), file=sys.stderr)
            sys.exit(1)
        except:
            print(_("Unable to read or parse the result page, it could be a "
                    "server timeout or a change server side, "
                    "try with another pastebin."), file=sys.stderr)
            sys.exit(1)

except KeyboardInterrupt:
    print(_("KeyboardInterrupt caught."), file=sys.stderr)
    sys.exit(1)
