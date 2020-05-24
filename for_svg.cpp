#include "for_svg.h"

int variant_9()
{
    int BLOCK_WIDTH=0;
    cerr<<"Enter the width of one block(int 3...30):";
    cin>>BLOCK_WIDTH;
    while (BLOCK_WIDTH<3 or BLOCK_WIDTH>30)
    {
        cerr<<"Wrong! The width must be between 3 and 30! Enter the width again!";
        cin>>BLOCK_WIDTH;
    }
    return BLOCK_WIDTH;
}

string GetInfoText()
{
    stringstream buffer;
    DWORD info = GetVersion();
    DWORD platform = info >> 16;
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD mask_major = 0x000000ff;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;
    buffer << "Windows v" << version_major << "." << version_minor;
    if ((info & 0x40000000) == 0) {
        DWORD build = platform;
        buffer << "(build " << build << ")\n";
    }
    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computer_name);
    GetComputerNameA(computer_name, &size);
    buffer << "Name: " << computer_name << "\n";
    return buffer.str();
}



void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='"<<baseline<<"'>"<<text<<"</text>";
}

void show_histogram_svg(const vector<size_t>& bins)
{
    const size_t screen_width=80;
    const size_t width=screen_width-4;
    int BLOCK_WIDTH=variant_9(); //comment for lab3
    const auto IMAGE_WIDTH=400*BLOCK_WIDTH/10; //comment for lab3
    //const auto IMAGE_WIDTH = 400; //comment for variant 9
    const auto IMAGE_HEIGHT = 400;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    //const auto BLOCK_WIDTH = 10; //comment for variant 9
    const auto GRAPH_WIDTH = IMAGE_WIDTH-TEXT_WIDTH;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    string stroke="black";
    string fill="red";
    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > width;

    if (scaling_needed)
    {
        const double scaling_multiplier = (double)width / max_count;
        if(max_count*BLOCK_WIDTH/GRAPH_WIDTH>1)
        {
            svg_text(TEXT_LEFT, TEXT_BASELINE, GetInfoText());
            for (size_t bin : bins)
            {
                const double new_scaling_multiplier=(double)GRAPH_WIDTH/(max_count*BLOCK_WIDTH*scaling_multiplier);
                const size_t new_bin_width = (size_t)BLOCK_WIDTH*bin*scaling_multiplier*new_scaling_multiplier;
                svg_text(TEXT_LEFT, top + TEXT_BASELINE * 3, to_string(bin));
                svg_rect(TEXT_WIDTH, top + TEXT_BASELINE * 2, new_bin_width, BIN_HEIGHT,stroke,fill);
                top += BIN_HEIGHT;
            }
        }
        else
        {
            svg_text(TEXT_LEFT, TEXT_BASELINE, GetInfoText());
            for (size_t bin : bins)
            {
                const double bin_width = BLOCK_WIDTH*bin*scaling_multiplier;
                svg_text(TEXT_LEFT, top + TEXT_BASELINE * 3, to_string(bin));
                svg_rect(TEXT_WIDTH, top + TEXT_BASELINE * 2, bin_width, BIN_HEIGHT,stroke,fill);
                top += BIN_HEIGHT;
            }
        }
    }

    else
    {
        if(max_count*BLOCK_WIDTH/GRAPH_WIDTH>1)
        {
            svg_text(TEXT_LEFT, TEXT_BASELINE, GetInfoText());
            for (size_t bin : bins)
            {
                const double new_scaling_multiplier=(double)GRAPH_WIDTH/(max_count*BLOCK_WIDTH);
                const size_t new_bin_width = (size_t)BLOCK_WIDTH*bin*new_scaling_multiplier;
                svg_text(TEXT_LEFT, top + TEXT_BASELINE * 3, to_string(bin));
                svg_rect(TEXT_WIDTH, top + TEXT_BASELINE * 2, new_bin_width, BIN_HEIGHT,stroke,fill);
                top += BIN_HEIGHT;
            }
        }
        else
        {
            svg_text(TEXT_LEFT, TEXT_BASELINE, GetInfoText());
            for (size_t bin : bins)
            {
                const double bin_width = BLOCK_WIDTH * bin;
                svg_text(TEXT_LEFT, top + TEXT_BASELINE * 3, to_string(bin));
                svg_rect(TEXT_WIDTH, top + TEXT_BASELINE * 2, bin_width, BIN_HEIGHT,stroke,fill);
                top += BIN_HEIGHT;
            }
        }
    }
    svg_end();
}
