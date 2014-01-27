// g++ glxtest.cpp -o glxtest -O2 -lX11 -L /usr/lib/nvidia/ -lGL -lXext
// gcc glinfo.c -o glinfo -O2 -lX11 -lGL -lXext

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glx.h>


int attribs[] = {
    GLX_DRAWABLE_TYPE, GLX_PIXMAP_BIT,
    GLX_X_RENDERABLE, True,
    0
};

int main()
{
    /* Open a connection to the X server */
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        printf("Unable to open a connection to the X server\n");
        exit(EXIT_FAILURE);
    }
    XSynchronize(dpy, True);

    GLXFBConfig          *fbConfigs;
    int                   numReturned;
    int glxVersionMajor;
    int glxVersionMinor;
    const char *serverVendor = glXQueryServerString(dpy, 0, GLX_VENDOR);
    const char *serverVersion = glXQueryServerString(dpy, 0, GLX_VERSION);
    const char *clientVendor = glXGetClientString(dpy, GLX_VENDOR);
    const char *clientVersion = glXGetClientString(dpy, GLX_VERSION);
      
    fbConfigs = glXChooseFBConfig(dpy, DefaultScreen(dpy), attribs, &numReturned );

    XVisualInfo *vInfo = glXGetVisualFromFBConfig(dpy, fbConfigs[0]);
    Pixmap pixmap = XCreatePixmap(dpy, RootWindow(dpy, vInfo->screen), 4, 4, 32);
    GLXPixmap glxpixmap = glXCreatePixmap(dpy,
                                          fbConfigs[0],
                                          pixmap,
                                          NULL);

    GLXContext context = glXCreateNewContext(dpy, fbConfigs[0], GLX_RGBA_TYPE, NULL, True);
    glXMakeCurrent(dpy, glxpixmap, context);
    printf("{\n");
    printf("	\"GL_VENDOR\": \"%s\",\n", glGetString(GL_VENDOR));
    printf("	\"GL_RENDERER\": \"%s\",\n", glGetString(GL_RENDERER));
    printf("	\"GL_VERSION\": \"%s\",\n", glGetString(GL_VERSION));
    printf("	\"SERVER_GLX_VENDOR\": \"%s\",\n", serverVendor);
    printf("	\"SERVER_GLX_VERSION\": \"%s\",\n", serverVersion);
    printf("	\"CLIENT_GLX_VENDOR\": \"%s\",\n", clientVendor);
    printf("	\"CLIENT_GLX_VERSION\": \"%s\",\n", clientVersion);
    if (! glXQueryVersion( dpy, & glxVersionMajor, & glxVersionMinor )) {
         fprintf(stderr, "Error: glXQueryVersion failed\n");
         exit(1);
    } else {
      printf("	\"GLX_VERSION\": \"%u.%u\"\n", glxVersionMajor, glxVersionMinor);
    }
    printf("}\n");
    exit( EXIT_SUCCESS );
}