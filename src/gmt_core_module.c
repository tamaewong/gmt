/* $Id$
 *
 * Copyright (c) 2012-2015
 * by P. Wessel, W. H. F. Smith, R. Scharroo, J. Luis, and F. Wobbe
 * See LICENSE.TXT file for copying and redistribution conditions.
 */

/* gmt_core_module.c populates the external array of GMT core
 * module parameters such as name, group and purpose strings.
 * This file also contains the following convenience function to
 * display all module purposes:
 *
 *   void gmt_core_module_show_all (struct GMTAPI_CTRL *API);
 *
 * Developers of external APIs for accessing GMT modules may use this
 * function to retrieve option keys needed for module arg processing:
 *
 *   char * gmt_core_module_info (void *API, const char *module);
 *
 * DO NOT edit this file directly! Regenerate thee file by running
 * 	gmt_make_module_src.sh core
 */
#include "gmt_dev.h"
#ifndef BUILD_SHARED_LIBS
#include "gmt_core_module.h"
#endif

static inline struct GMTAPI_CTRL * gmt_get_api_ptr (struct GMTAPI_CTRL *ptr) {return (ptr);}

/* Sorted array with information for all GMT core modules */

/* name, library, and purpose for each module */
struct Gmt_moduleinfo {
	const char *name;             /* Program name */
	const char *component;        /* Component (core, supplement, custom) */
	const char *purpose;          /* Program purpose */
	const char *keys;             /* Program option info for external APIs */
#ifndef BUILD_SHARED_LIBS
	/* gmt module function pointer: */
	int (*p_func)(void*, int, void*);
#endif
};

struct Gmt_moduleinfo g_core_module[] = {
#ifdef BUILD_SHARED_LIBS
	{"blockmean", "core", "Block average (x,y,z) data tables by L2 norm", "<DI,>DO,RGi"},
	{"blockmedian", "core", "Block average (x,y,z) data tables by L1 norm (spatial median)", "<DI,>DO,RGi"},
	{"blockmode", "core", "Block average (x,y,z) data tables by mode estimation", "<DI,>DO,RGi"},
	{"filter1d", "core", "Do time domain filtering of 1-D data tables", "<DI,>DO"},
	{"fitcircle", "core", "Find mean position and best-fitting great- or small-circle to points on sphere", "<DI,>TO"},
	{"gmt2kml", "core", "Convert GMT data tables to KML files for Google Earth", "<DI,>TO"},
	{"gmtconnect", "core", "Connect individual lines whose end points match within tolerance", "<DI,>DO,CDo,LTo,QTo"},
	{"gmtconvert", "core", "Convert, paste, or extract columns from data tables", "<DI,>DO"},
	{"gmtdefaults", "core", "List current GMT default parameters", ""},
	{"gmtget", "core", "Get individual GMT default parameters", ">TO"},
	{"gmtinfo", "core", "Get information about data tables", "<DI,>TO,>DC"},
	{"gmtlogo", "core", "Plot the GMT logo on maps", ""},
	{"gmtmath", "core", "Reverse Polish Notation (RPN) calculator for data tables", "<DI,ADi,>DO"},
	{"gmtread", "core", "Read GMT objects into external API", "<?I,>?O,-T-"},
	{"gmtregress", "core", "Perform linear regression of 1-D data sets", "<DI,>DO"},
	{"gmtselect", "core", "Select data table subsets based on multiple spatial criteria", "<DI,CDi,FDi,LDi,>DO,RGi"},
	{"gmtset", "core", "Change individual GMT default parameters", ""},
	{"gmtsimplify", "core", "Line reduction using the Douglas-Peucker algorithm", "<DI,>DO"},
	{"gmtspatial", "core", "Do geospatial operations on lines and polygons", "<DI,DDi,NDi,TDi,>DO"},
	{"gmtvector", "core", "Basic manipulation of Cartesian vectors", "<DI,ADi,>DO"},
	{"gmtwhich", "core", "Find full path to specified files", "<TI,>TO"},
	{"gmtwrite", "core", "Write GMT objects from external API", "<?I,>?O,-T-"},
	{"grd2cpt", "core", "Make linear or histogram-equalized color palette table from grid", "<GI,>CO,RGi"},
	{"grd2rgb", "core", "Write r/g/b grid files from a grid file, a raw RGB file, or SUN rasterfile", "<GI,RGi"},
	{"grd2xyz", "core", "Convert grid file to data table", "<GI,>DO,RGi"},
	{"grdblend", "core", "Blend several partially over-lapping grids into one larger grid", "<TI,GGO,RGi"},
	{"grdclip", "core", "Clip the range of grids", "<GI,GGO,RGi"},
	{"grdcontour", "core", "Make contour map using a grid", "<GI,CCi,>DD,>XO,RGi"},
	{"grdconvert", "core", "Convert between different grid formats", "<GI,>GO,RGi"},
	{"grdcut", "core", "Extract subregion from a grid", "<GI,GGO,RGi"},
	{"grdedit", "core", "Modify header or content of a grid", "<GI,NDi,GGO,RGi"},
	{"grdfft", "core", "Do mathematical operations on grids in the wavenumber (or frequency) domain", "<GI,GGO,RGi"},
	{"grdfilter", "core", "Filter a grid in the space (or time) domain", "<GI,GGO,RGi"},
	{"grdgradient", "core", "Compute directional gradients from a grid", "<GI,GGO,SGo,RGi"},
	{"grdhisteq", "core", "Perform histogram equalization for a grid", "<GI,GGO,DTo,RGi"},
	{"grdimage", "core", "Project grids or images and plot them on maps", "<GI,CCi,IGi,>XO,RGi"},
	{"grdinfo", "core", "Extract information from grids", "<GI,>TO,>DC,RGi"},
	{"grdlandmask", "core", "Create a \"wet-dry\" mask grid from shoreline data base", "GGO,RGi"},
	{"grdmask", "core", "Create mask grid from polygons or point coverage", "<DI,GGO,RGi"},
	{"grdmath", "core", "Reverse Polish Notation (RPN) calculator for grids (element by element)", "<GI,=GO,RGi"},
	{"grdpaste", "core", "Join two grids along their common edge", "<GI,GGO,RGi"},
	{"grdproject", "core", "Forward and inverse map transformation of grids", "<GI,GGO,RGi"},
	{"grdraster", "core", "Extract subregion from a binary raster and save as a GMT grid", "GGO,TDo,RGi"},
	{"grdsample", "core", "Resample a grid onto a new lattice", "<GI,GGO,RGi"},
	{"grdtrack", "core", "Sample grids at specified (x,y) locations", "<DI,DDo,GGi,>DO,RGi"},
	{"grdtrend", "core", "Fit trend surface to grids and compute residuals", "<GI,DGo,TGo,WGo,RGi"},
	{"grdvector", "core", "Plot vector field from two component grids", "<GI,CCi,>XO,RGi"},
	{"grdview", "core", "Create 3-D perspective image or surface mesh from a grid", "<GI,CCi,GGi,IGi,>XO,RGi"},
	{"grdvolume", "core", "Calculate grid volume and area constrained by a contour", "<GI,>DO,RGi"},
	{"greenspline", "core", "Interpolate using Green's functions for splines in 1-3 dimensions", "<DI,ADi,NDi,TGi,CDo,GGO,RGi"},
	{"kml2gmt", "core", "Extract GMT table data from Google Earth KML files", "<TI,>DO"},
	{"makecpt", "core", "Make GMT color palette tables", ">CO"},
	{"mapproject", "core", "Do forward and inverse map transformations, datum conversions and geodesy", "<DI,LDi,>DO,W-i,RGi"},
	{"nearneighbor", "core", "Grid table data using a \"Nearest neighbor\" algorithm", "<DI,GGO,RGi"},
	{"project", "core", "Project table data onto lines or great circles, generate tracks, or translate coordinates", "<DI,>DO,G-i"},
	{"psbasemap", "core", "Plot base maps and frames", ">XO,RGi"},
	{"psclip", "core", "Initialize or terminate polygonal clip paths", "<DI,>XO"},
	{"pscoast", "core", "Plot continents, countries, shorelines, rivers, and borders on maps", ">XO,>DM,RGi"},
	{"pscontour", "core", "Contour table data by direct triangulation", "<DI,CCi,EDi,>DD,>XO,RGi"},
	{"psconvert", "core", "Convert [E]PS file(s) to other formats using GhostScript", "FIo"},
	{"pshistogram", "core", "Calculate and plot histograms", "<DI,>XO,>Do"},
	{"psimage", "core", "Place images or EPS files on maps", "<II,>XO,RGi"},
	{"pslegend", "core", "Plot legends on maps", "<TI,ACi,>XO,RGi"},
	{"psmask", "core", "Use data tables to clip or mask map areas with no coverage", "<DI,>DD,C-i,>XO,RGi"},
	{"psrose", "core", "Plot a polar histogram (rose, sector, windrose diagrams)", "<DI,>XO"},
	{"psscale", "core", "Plot a gray-scale or color-scale on maps", "CCI,>XO"},
	{"pstext", "core", "Plot or typeset text on maps", "<TI,>XO,RGi"},
	{"pswiggle", "core", "Plot z = f(x,y) anomalies along tracks", "<DI,>XO,RGi"},
	{"psxyz", "core", "Plot lines, polygons, and symbols in 3-D", "<DI,CCi,T-i,>XO,RGi"},
	{"psxy", "core", "Plot lines, polygons, and symbols on maps", "<DI,CCi,T-i,>XO,RGi"},
	{"sample1d", "core", "Resample 1-D table data using splines", "<DI,NDi,>DO"},
	{"spectrum1d", "core", "Compute auto- [and cross-] spectra from one [or two] timeseries", "<DI,>DO"},
	{"sph2grd", "core", "Compute grid from spherical harmonic coefficients", "<DI,GGO,RGi"},
	{"sphdistance", "core", "Make Voronoi distance, node, or nearest-neighbor grid on a sphere", "<DI,NDi,QDi,GGO,RGi"},
	{"sphinterpolate", "core", "Spherical gridding in tension of data on a sphere", "<DI,GGO,RGi"},
	{"sphtriangulate", "core", "Delaunay or Voronoi construction of spherical lon,lat data", "<DI,>DO,NDo,RGi"},
	{"splitxyz", "core", "Split xyz[dh] data tables into individual segments", "<DI,>DO"},
	{"surface", "core", "Grid table data using adjustable tension continuous curvature splines", "<DI,DDi,LGi,GGO,RGi"},
	{"trend1d", "core", "Fit a [weighted] [robust] polynomial [and/or Fourier] model for y = f(x) to xy[w] data", "<DI,>DO"},
	{"trend2d", "core", "Fit a [weighted] [robust] polynomial for z = f(x,y) to xyz[w] data", "<DI,>DO"},
	{"triangulate", "core", "Do optimal (Delaunay) triangulation and gridding of Cartesian table data", "<DI,>DO,GGo,RGi"},
	{"xyz2grd", "core", "Convert data table to a grid file", "<DI,SDo,GGO,RGi"},
	{NULL, NULL, NULL, NULL} /* last element == NULL detects end of array */
#else
	{"blockmean", "core", "Block average (x,y,z) data tables by L2 norm", "<DI,>DO,RGi", &GMT_blockmean},
	{"blockmedian", "core", "Block average (x,y,z) data tables by L1 norm (spatial median)", "<DI,>DO,RGi", &GMT_blockmedian},
	{"blockmode", "core", "Block average (x,y,z) data tables by mode estimation", "<DI,>DO,RGi", &GMT_blockmode},
	{"filter1d", "core", "Do time domain filtering of 1-D data tables", "<DI,>DO", &GMT_filter1d},
	{"fitcircle", "core", "Find mean position and best-fitting great- or small-circle to points on sphere", "<DI,>TO", &GMT_fitcircle},
	{"gmt2kml", "core", "Convert GMT data tables to KML files for Google Earth", "<DI,>TO", &GMT_gmt2kml},
	{"gmtconnect", "core", "Connect individual lines whose end points match within tolerance", "<DI,>DO,CDo,LTo,QTo", &GMT_gmtconnect},
	{"gmtconvert", "core", "Convert, paste, or extract columns from data tables", "<DI,>DO", &GMT_gmtconvert},
	{"gmtdefaults", "core", "List current GMT default parameters", "", &GMT_gmtdefaults},
	{"gmtget", "core", "Get individual GMT default parameters", ">TO", &GMT_gmtget},
	{"gmtinfo", "core", "Get information about data tables", "<DI,>TO,>DC", &GMT_gmtinfo},
	{"gmtlogo", "core", "Plot the GMT logo on maps", "", &GMT_gmtlogo},
	{"gmtmath", "core", "Reverse Polish Notation (RPN) calculator for data tables", "<DI,ADi,>DO", &GMT_gmtmath},
	{"gmtread", "core", "Read GMT objects into external API", "<?I,>?O,-T-", &GMT_gmtread},
	{"gmtregress", "core", "Perform linear regression of 1-D data sets", "<DI,>DO", &GMT_gmtregress},
	{"gmtselect", "core", "Select data table subsets based on multiple spatial criteria", "<DI,CDi,FDi,LDi,>DO,RGi", &GMT_gmtselect},
	{"gmtset", "core", "Change individual GMT default parameters", "", &GMT_gmtset},
	{"gmtsimplify", "core", "Line reduction using the Douglas-Peucker algorithm", "<DI,>DO", &GMT_gmtsimplify},
	{"gmtspatial", "core", "Do geospatial operations on lines and polygons", "<DI,DDi,NDi,TDi,>DO", &GMT_gmtspatial},
	{"gmtvector", "core", "Basic manipulation of Cartesian vectors", "<DI,ADi,>DO", &GMT_gmtvector},
	{"gmtwhich", "core", "Find full path to specified files", "<TI,>TO", &GMT_gmtwhich},
	{"gmtwrite", "core", "Write GMT objects from external API", "<?I,>?O,-T-", &GMT_gmtwrite},
	{"grd2cpt", "core", "Make linear or histogram-equalized color palette table from grid", "<GI,>CO,RGi", &GMT_grd2cpt},
	{"grd2rgb", "core", "Write r/g/b grid files from a grid file, a raw RGB file, or SUN rasterfile", "<GI,RGi", &GMT_grd2rgb},
	{"grd2xyz", "core", "Convert grid file to data table", "<GI,>DO,RGi", &GMT_grd2xyz},
	{"grdblend", "core", "Blend several partially over-lapping grids into one larger grid", "<TI,GGO,RGi", &GMT_grdblend},
	{"grdclip", "core", "Clip the range of grids", "<GI,GGO,RGi", &GMT_grdclip},
	{"grdcontour", "core", "Make contour map using a grid", "<GI,CCi,>DD,>XO,RGi", &GMT_grdcontour},
	{"grdconvert", "core", "Convert between different grid formats", "<GI,>GO,RGi", &GMT_grdconvert},
	{"grdcut", "core", "Extract subregion from a grid", "<GI,GGO,RGi", &GMT_grdcut},
	{"grdedit", "core", "Modify header or content of a grid", "<GI,NDi,GGO,RGi", &GMT_grdedit},
	{"grdfft", "core", "Do mathematical operations on grids in the wavenumber (or frequency) domain", "<GI,GGO,RGi", &GMT_grdfft},
	{"grdfilter", "core", "Filter a grid in the space (or time) domain", "<GI,GGO,RGi", &GMT_grdfilter},
	{"grdgradient", "core", "Compute directional gradients from a grid", "<GI,GGO,SGo,RGi", &GMT_grdgradient},
	{"grdhisteq", "core", "Perform histogram equalization for a grid", "<GI,GGO,DTo,RGi", &GMT_grdhisteq},
	{"grdimage", "core", "Project grids or images and plot them on maps", "<GI,CCi,IGi,>XO,RGi", &GMT_grdimage},
	{"grdinfo", "core", "Extract information from grids", "<GI,>TO,>DC,RGi", &GMT_grdinfo},
	{"grdlandmask", "core", "Create a \"wet-dry\" mask grid from shoreline data base", "GGO,RGi", &GMT_grdlandmask},
	{"grdmask", "core", "Create mask grid from polygons or point coverage", "<DI,GGO,RGi", &GMT_grdmask},
	{"grdmath", "core", "Reverse Polish Notation (RPN) calculator for grids (element by element)", "<GI,=GO,RGi", &GMT_grdmath},
	{"grdpaste", "core", "Join two grids along their common edge", "<GI,GGO,RGi", &GMT_grdpaste},
	{"grdproject", "core", "Forward and inverse map transformation of grids", "<GI,GGO,RGi", &GMT_grdproject},
	{"grdraster", "core", "Extract subregion from a binary raster and save as a GMT grid", "GGO,TDo,RGi", &GMT_grdraster},
	{"grdsample", "core", "Resample a grid onto a new lattice", "<GI,GGO,RGi", &GMT_grdsample},
	{"grdtrack", "core", "Sample grids at specified (x,y) locations", "<DI,DDo,GGi,>DO,RGi", &GMT_grdtrack},
	{"grdtrend", "core", "Fit trend surface to grids and compute residuals", "<GI,DGo,TGo,WGo,RGi", &GMT_grdtrend},
	{"grdvector", "core", "Plot vector field from two component grids", "<GI,CCi,>XO,RGi", &GMT_grdvector},
	{"grdview", "core", "Create 3-D perspective image or surface mesh from a grid", "<GI,CCi,GGi,IGi,>XO,RGi", &GMT_grdview},
	{"grdvolume", "core", "Calculate grid volume and area constrained by a contour", "<GI,>DO,RGi", &GMT_grdvolume},
	{"greenspline", "core", "Interpolate using Green's functions for splines in 1-3 dimensions", "<DI,ADi,NDi,TGi,CDo,GGO,RGi", &GMT_greenspline},
	{"kml2gmt", "core", "Extract GMT table data from Google Earth KML files", "<TI,>DO", &GMT_kml2gmt},
	{"makecpt", "core", "Make GMT color palette tables", ">CO", &GMT_makecpt},
	{"mapproject", "core", "Do forward and inverse map transformations, datum conversions and geodesy", "<DI,LDi,>DO,W-i,RGi", &GMT_mapproject},
	{"nearneighbor", "core", "Grid table data using a \"Nearest neighbor\" algorithm", "<DI,GGO,RGi", &GMT_nearneighbor},
	{"project", "core", "Project table data onto lines or great circles, generate tracks, or translate coordinates", "<DI,>DO,G-i", &GMT_project},
	{"psbasemap", "core", "Plot base maps and frames", ">XO,RGi", &GMT_psbasemap},
	{"psclip", "core", "Initialize or terminate polygonal clip paths", "<DI,>XO", &GMT_psclip},
	{"pscoast", "core", "Plot continents, countries, shorelines, rivers, and borders on maps", ">XO,>DM,RGi", &GMT_pscoast},
	{"pscontour", "core", "Contour table data by direct triangulation", "<DI,CCi,EDi,>DD,>XO,RGi", &GMT_pscontour},
	{"psconvert", "core", "Convert [E]PS file(s) to other formats using GhostScript", "FIo", &GMT_psconvert},
	{"pshistogram", "core", "Calculate and plot histograms", "<DI,>XO,>Do", &GMT_pshistogram},
	{"psimage", "core", "Place images or EPS files on maps", "<II,>XO,RGi", &GMT_psimage},
	{"pslegend", "core", "Plot legends on maps", "<TI,ACi,>XO,RGi", &GMT_pslegend},
	{"psmask", "core", "Use data tables to clip or mask map areas with no coverage", "<DI,>DD,C-i,>XO,RGi", &GMT_psmask},
	{"psrose", "core", "Plot a polar histogram (rose, sector, windrose diagrams)", "<DI,>XO", &GMT_psrose},
	{"psscale", "core", "Plot a gray-scale or color-scale on maps", "CCI,>XO", &GMT_psscale},
	{"pstext", "core", "Plot or typeset text on maps", "<TI,>XO,RGi", &GMT_pstext},
	{"pswiggle", "core", "Plot z = f(x,y) anomalies along tracks", "<DI,>XO,RGi", &GMT_pswiggle},
	{"psxyz", "core", "Plot lines, polygons, and symbols in 3-D", "<DI,CCi,T-i,>XO,RGi", &GMT_psxyz},
	{"psxy", "core", "Plot lines, polygons, and symbols on maps", "<DI,CCi,T-i,>XO,RGi", &GMT_psxy},
	{"sample1d", "core", "Resample 1-D table data using splines", "<DI,NDi,>DO", &GMT_sample1d},
	{"spectrum1d", "core", "Compute auto- [and cross-] spectra from one [or two] timeseries", "<DI,>DO", &GMT_spectrum1d},
	{"sph2grd", "core", "Compute grid from spherical harmonic coefficients", "<DI,GGO,RGi", &GMT_sph2grd},
	{"sphdistance", "core", "Make Voronoi distance, node, or nearest-neighbor grid on a sphere", "<DI,NDi,QDi,GGO,RGi", &GMT_sphdistance},
	{"sphinterpolate", "core", "Spherical gridding in tension of data on a sphere", "<DI,GGO,RGi", &GMT_sphinterpolate},
	{"sphtriangulate", "core", "Delaunay or Voronoi construction of spherical lon,lat data", "<DI,>DO,NDo,RGi", &GMT_sphtriangulate},
	{"splitxyz", "core", "Split xyz[dh] data tables into individual segments", "<DI,>DO", &GMT_splitxyz},
	{"surface", "core", "Grid table data using adjustable tension continuous curvature splines", "<DI,DDi,LGi,GGO,RGi", &GMT_surface},
	{"trend1d", "core", "Fit a [weighted] [robust] polynomial [and/or Fourier] model for y = f(x) to xy[w] data", "<DI,>DO", &GMT_trend1d},
	{"trend2d", "core", "Fit a [weighted] [robust] polynomial for z = f(x,y) to xyz[w] data", "<DI,>DO", &GMT_trend2d},
	{"triangulate", "core", "Do optimal (Delaunay) triangulation and gridding of Cartesian table data", "<DI,>DO,GGo,RGi", &GMT_triangulate},
	{"xyz2grd", "core", "Convert data table to a grid file", "<DI,SDo,GGO,RGi", &GMT_xyz2grd},
	{NULL, NULL, NULL, NULL, NULL} /* last element == NULL detects end of array */
#endif
};

/* Pretty print all GMT core module names and their purposes */
void gmt_core_module_show_all (void *V_API) {
	unsigned int module_id = 0;
	char message[256];
	struct GMTAPI_CTRL *API = gmt_get_api_ptr (V_API);
	GMT_Message (V_API, GMT_TIME_NONE, "\n===  GMT core: The main modules of the Generic Mapping Tools  ===\n");
	while (g_core_module[module_id].name != NULL) {
		if (module_id == 0 || strcmp (g_core_module[module_id-1].component, g_core_module[module_id].component)) {
			/* Start of new supplemental group */
			sprintf (message, "\nModule name:     Purpose of %s module:\n", g_core_module[module_id].component);
			GMT_Message (V_API, GMT_TIME_NONE, message);
			GMT_Message (V_API, GMT_TIME_NONE, "----------------------------------------------------------------\n");
		}
		if (API->mode || (strcmp (g_core_module[module_id].name, "read") && strcmp (g_core_module[module_id].name, "write"))) {
			sprintf (message, "%-16s %s\n",
				g_core_module[module_id].name, g_core_module[module_id].purpose);
				GMT_Message (V_API, GMT_TIME_NONE, message);
		}
		++module_id;
	}
}

/* Lookup module id by name, return option keys pointer (for external API developers) */
const char *gmt_core_module_info (void *API, char *candidate) {
	int module_id = 0;

	/* Match actual_name against g_module[module_id].name */
	while (g_core_module[module_id].name != NULL &&
	       strcmp (candidate, g_core_module[module_id].name))
		++module_id;

	/* Return Module keys or NULL */
	return (g_core_module[module_id].keys);
}
	
#ifndef BUILD_SHARED_LIBS
/* Lookup module id by name, return function pointer */
void *gmt_core_module_lookup (void *API, const char *candidate) {
	int module_id = 0;

	/* Match actual_name against g_module[module_id].name */
	while (g_core_module[module_id].name != NULL &&
	       strcmp (candidate, g_core_module[module_id].name))
		++module_id;

	/* Return Module function or NULL */
	return (g_core_module[module_id].p_func);
}
#endif
