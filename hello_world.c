/* geos_hello_world.c */

#include <stdio.h>  /* for printf */
#include <stdarg.h> /* for va_list */

/* Only the CAPI header is required */
#include <geos_c.h>

/*
* GEOS requires two message handlers to return
* error and notice message to the calling program.
*
*   typedef void(* GEOSMessageHandler) (const char *fmt,...)
*
* Here we stub out an example that just prints the
* messages to stdout.
*/
static void
geos_msg_handler(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintf (fmt, ap);
    va_end(ap);
}

int main()
{
    /* Send notice and error messages to the terminal */
    initGEOS(geos_msg_handler, geos_msg_handler);

    /* Read WKT into geometry object */
    GEOSWKTReader* reader = GEOSWKTReader_create();
    GEOSGeometry* geom_a = GEOSWKTReader_read(reader, "POINT(1 1)");

    /* Convert result to WKT */
    GEOSWKTWriter* writer = GEOSWKTWriter_create();
    char* wkt = GEOSWKTWriter_write(writer, geom_a);
    printf("Geometry: %s\n", wkt);

    /* Clean up allocated objects */
    GEOSWKTReader_destroy(reader);
    GEOSWKTWriter_destroy(writer);
    GEOSGeom_destroy(geom_a);
    GEOSFree(wkt);

    /* Clean up the global context */
    finishGEOS();
    return 0;
}