#pragma once
#include "type.h"
namespace kengine {
	class RGBA
	{
	public:
		RGBA(){}
		char r() { return data.b[0]; }
		char g() { return data.b[1]; }
		char b() { return data.b[2]; }
		char a() { return data.b[3]; }

		int32 i() { return data.i; }
	private:
		union ColorData
		{
			int32 i;
			char b[4];
		};
		ColorData data;
	};

	class Color
	{
	public:
		float r;
		float g;
		float b;
		float a;
		Color() : r(0.), g(0.), b(0.), a(0.) {}
		Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
		Color(float r, float g, float b) : r(r), g(g), b(b), a(1.0f) {}
		~Color() {}

		bool operator ==(Color c) {
			return this->r == c.r && this->g == c.g && this->b == c.b && this->a == c.a;
		}

		void to_hsl() {}
		RGBA get_component() {}
	};
	

	#define color_aliceblue			Color(0.94f, 0.97f, 1.00f)
	#define color_antiquewhite		Color(0.98f, 0.92f, 0.84f)
	#define color_aqua				Color(0.00f, 1.00f, 1.00f)
	#define color_aquamarine		Color(0.50f, 1.00f, 0.83f)
	#define color_azure				Color(0.94f, 1.00f, 1.00f)
	#define color_beige				Color(0.96f, 0.96f, 0.86f)
	#define color_bisque			Color(1.00f, 0.89f, 0.77f)
	#define color_black				Color(0.00f, 0.00f, 0.00f)
	#define color_blanchedalmond	Color(1.00f, 0.92f, 0.80f)
	#define color_blue				Color(0.00f, 0.00f, 1.00f)
	#define color_blueviolet		Color(0.54f, 0.17f, 0.89f)
	#define color_brown				Color(0.65f, 0.16f, 0.16f)
	#define color_burlywood  		Color(0.87f, 0.72f, 0.53f)
	#define color_cadetblue  		Color(0.37f, 0.62f, 0.63f)
	#define color_chartreuse  		Color(0.50f, 1.00f, 0.00f)
	#define color_chocolate  		Color(0.82f, 0.41f, 0.12f)
	#define color_coral  			Color(1.00f, 0.50f, 0.31f)
	#define color_cornflower  		Color(0.39f, 0.58f, 0.93f)
	#define color_cornsilk  		Color(1.00f, 0.97f, 0.86f)
	#define color_crimson  			Color(0.86f, 0.08f, 0.24f)
	#define color_cyan  			Color(0.00f, 1.00f, 1.00f)
	#define color_darkblue  		Color(0.00f, 0.00f, 0.55f)
	#define color_darkcyan  		Color(0.00f, 0.55f, 0.55f)
	#define color_darkgoldenrod  	Color(0.72f, 0.53f, 0.04f)
	#define color_darkgray  		Color(0.66f, 0.66f, 0.66f)
	#define color_darkgreen  		Color(0.00f, 0.39f, 0.00f)
	#define color_darkkhaki  		Color(0.74f, 0.72f, 0.42f)
	#define color_darkmagenta  		Color(0.55f, 0.00f, 0.55f)
	#define color_darkolivegreen  	Color(0.33f, 0.42f, 0.18f)
	#define color_darkorange  		Color(1.00f, 0.55f, 0.00f)
	#define color_darkorchid  		Color(0.60f, 0.20f, 0.80f)
	#define color_darkred  			Color(0.55f, 0.00f, 0.00f)
	#define color_darksalmon  		Color(0.91f, 0.59f, 0.48f)
	#define color_darkseagreen  	Color(0.56f, 0.74f, 0.56f)
	#define color_darkslateblue  	Color(0.28f, 0.24f, 0.55f)
	#define color_darkslategray  	Color(0.18f, 0.31f, 0.31f)
	#define color_darkturquoise  	Color(0.00f, 0.81f, 0.82f)
	#define color_darkviolet  		Color(0.58f, 0.00f, 0.83f)
	#define color_deeppink  		Color(1.00f, 0.08f, 0.58f)
	#define color_deepskyblue  		Color(0.00f, 0.75f, 1.00f)
	#define color_dimgray  			Color(0.41f, 0.41f, 0.41f)
	#define color_dodgerblue  		Color(0.12f, 0.56f, 1.00f)
	#define color_firebrick  		Color(0.70f, 0.13f, 0.13f)
	#define color_floralwhite  		Color(1.00f, 0.98f, 0.94f)
	#define color_forestgreen  		Color(0.13f, 0.55f, 0.13f)
	#define color_fuchsia  			Color(1.00f, 0.00f, 1.00f)
	#define color_gainsboro  		Color(0.86f, 0.86f, 0.86f)
	#define color_ghostwhite  		Color(0.97f, 0.97f, 1.00f)
	#define color_gold  			Color(1.00f, 0.84f, 0.00f)
	#define color_goldenrod  		Color(0.85f, 0.65f, 0.13f)
	#define color_gray 	 			Color(0.75f, 0.75f, 0.75f)
	#define color_webgray  			Color(0.50f, 0.50f, 0.50f)
	#define color_green  			Color(0.00f, 1.00f, 0.00f)
	#define color_webgreen  		Color(0.00f, 0.50f, 0.00f)
	#define color_greenyellow  		Color(0.68f, 1.00f, 0.18f)
	#define color_honeydew  		Color(0.94f, 1.00f, 0.94f)
	#define color_hotpink  			Color(1.00f, 0.41f, 0.71f)
	#define color_indianred  		Color(0.80f, 0.36f, 0.36f)
	#define color_indigo 			Color(0.29f, 0.00f, 0.51f)
	#define color_ivory  			Color(1.00f, 1.00f, 0.94f)
	#define color_khaki  			Color(0.94f, 0.90f, 0.55f)
	#define color_lavender  		Color(0.90f, 0.90f, 0.98f)
	#define color_lavenderblush  	Color(1.00f, 0.94f, 0.96f)
	#define color_lawngreen  		Color(0.49f, 0.99f, 0.00f)
	#define color_lemonchiffon  	Color(1.00f, 0.98f, 0.80f)
	#define color_lightblue  		Color(0.68f, 0.85f, 0.90f)
	#define color_lightcoral  		Color(0.94f, 0.50f, 0.50f)
	#define color_lightcyan  		Color(0.88f, 1.00f, 1.00f)
	#define color_lightgoldenrod  	Color(0.98f, 0.98f, 0.82f)
	#define color_lightgray  		Color(0.83f, 0.83f, 0.83f)
	#define color_lightgreen  		Color(0.56f, 0.93f, 0.56f)
	#define color_lightpink  		Color(1.00f, 0.71f, 0.76f)
	#define color_lightsalmon  		Color(1.00f, 0.63f, 0.48f)
	#define color_lightseagreen  	Color(0.13f, 0.70f, 0.67f)
	#define color_lightskyblue  	Color(0.53f, 0.81f, 0.98f)
	#define color_lightslategray  	Color(0.47f, 0.53f, 0.60f)
	#define color_lightsteelblue  	Color(0.69f, 0.77f, 0.87f)
	#define color_lightyellow  		Color(1.00f, 1.00f, 0.88f)
	#define color_lime  			Color(0.00f, 1.00f, 0.00f)
	#define color_limegreen  		Color(0.20f, 0.80f, 0.20f)
	#define color_linen  			Color(0.98f, 0.94f, 0.90f)
	#define color_magenta  			Color(1.00f, 0.00f, 1.00f)
	#define color_maroon  			Color(0.69f, 0.19f, 0.38f)
	#define color_webmaroon  		Color(0.50f, 0.00f, 0.00f)
	#define color_mediumaquamarine  Color(0.40f, 0.80f, 0.67f)
	#define color_mediumblue 	 	Color(0.00f, 0.00f, 0.80f)
	#define color_mediumorchid  	Color(0.73f, 0.33f, 0.83f)
	#define color_mediumpurple  	Color(0.58f, 0.44f, 0.86f)
	#define color_mediumseagreen  	Color(0.24f, 0.70f, 0.44f)
	#define color_mediumslateblue  	Color(0.48f, 0.41f, 0.93f)
	#define color_mediumspringgreen Color(0.00f, 0.98f, 0.60f)
	#define color_mediumturquoise  	Color(0.28f, 0.82f, 0.80f)
	#define color_mediumvioletred  	Color(0.78f, 0.08f, 0.52f)
	#define color_midnightblue  	Color(0.10f, 0.10f, 0.44f)
	#define color_mintcream  		Color(0.96f, 1.00f, 0.98f)
	#define color_mistyrose  		Color(1.00f, 0.89f, 0.88f)
	#define color_moccasin  		Color(1.00f, 0.89f, 0.71f)
	#define color_navajowhite  		Color(1.00f, 0.87f, 0.68f)
	#define color_navyblue  		Color(0.00f, 0.00f, 0.50f)
	#define color_oldlace  			Color(0.99f, 0.96f, 0.90f)
	#define color_olive  			Color(0.50f, 0.50f, 0.00f)
	#define color_olivedrab  		Color(0.42f, 0.56f, 0.14f)
	#define color_orange  			Color(1.00f, 0.65f, 0.00f)
	#define color_orangered  		Color(1.00f, 0.27f, 0.00f)
	#define color_orchid  			Color(0.85f, 0.44f, 0.84f)
	#define color_palegoldenrod  	Color(0.93f, 0.91f, 0.67f)
	#define color_palegreen  		Color(0.60f, 0.98f, 0.60f)
	#define color_paleturquoise  	Color(0.69f, 0.93f, 0.93f)
	#define color_palevioletred  	Color(0.86f, 0.44f, 0.58f)
	#define color_papayawhip  		Color(1.00f, 0.94f, 0.84f)
	#define color_peachpuff  		Color(1.00f, 0.85f, 0.73f)
	#define color_peru  			Color(0.80f, 0.52f, 0.25f)
	#define color_pink  			Color(1.00f, 0.75f, 0.80f)
	#define color_plum  			Color(0.87f, 0.63f, 0.87f)
	#define color_powderblue  		Color(0.69f, 0.88f, 0.90f)
	#define color_purple  			Color(0.63f, 0.13f, 0.94f)
	#define color_webpurple  		Color(0.50f, 0.00f, 0.50f)
	#define color_rebeccapurple  	Color(0.40f, 0.20f, 0.60f)
	#define color_red  				Color(1.00f, 0.00f, 0.00f)
	#define color_rosybrown  		Color(0.74f, 0.56f, 0.56f)
	#define color_royalblue  		Color(0.25f, 0.41f, 0.88f)
	#define color_saddlebrown  		Color(0.55f, 0.27f, 0.07f)
	#define color_salmon  			Color(0.98f, 0.50f, 0.45f)
	#define color_sandybrown  		Color(0.96f, 0.64f, 0.38f)
	#define color_seagreen  		Color(0.18f, 0.55f, 0.34f)
	#define color_seashell  		Color(1.00f, 0.96f, 0.93f)
	#define color_sienna  			Color(0.63f, 0.32f, 0.18f)
	#define color_silver  			Color(0.75f, 0.75f, 0.75f)
	#define color_skyblue  			Color(0.53f, 0.81f, 0.92f)
	#define color_slateblue  		Color(0.42f, 0.35f, 0.80f)
	#define color_slategray  		Color(0.44f, 0.50f, 0.56f)
	#define color_snow  			Color(1.00f, 0.98f, 0.98f)
	#define color_springgreen  		Color(0.00f, 1.00f, 0.50f)
	#define color_steelblue  		Color(0.27f, 0.51f, 0.71f)
	#define color_tan  				Color(0.82f, 0.71f, 0.55f)
	#define color_teal  			Color(0.00f, 0.50f, 0.50f)
	#define color_thistle  			Color(0.85f, 0.75f, 0.85f)
	#define color_tomato  			Color(1.00f, 0.39f, 0.28f)
	#define color_turquoise  		Color(0.25f, 0.88f, 0.82f)
	#define color_transparent  		Color(1.00f, 1.00f, 1.00f, 0.00f)
	#define color_violet  			Color(0.93f, 0.51f, 0.93f)
	#define color_wheat  			Color(0.96f, 0.87f, 0.70f)
	#define color_white  			Color(1.00f, 1.00f, 1.00f)
	#define color_whitesmoke  		Color(0.96f, 0.96f, 0.96f)
	#define color_yellow  			Color(1.00f, 1.00f, 0.00f)
	#define color_yellowgreen  		Color(0.60f, 0.80f, 0.20f)
}
