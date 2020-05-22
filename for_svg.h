#ifndef FOR_SVG_H_INCLUDED
#define FOR_SVG_H_INCLUDED
#include <vector>
#include <string>
using namespace std;
int variant_9();
void svg_begin(double width, double height);
void svg_end();
void svg_rect(double x, double y, double width, double height, string stroke, string fill);
void svg_text(double left, double baseline, string text);
void show_histogram_svg(const vector<size_t>& bins);


#endif // FOR_SVG_H_INCLUDED
