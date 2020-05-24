#include <iostream>
#include <vector>
#include <windows.h>
#include "histogram.h"
#include "for_svg.h"

using namespace std;

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}
int main()
{
    DWORD info = GetVersion();
    DWORD platform = info >> 16;
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    DWORD mask_major = 0x000000ff;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;
    printf("Major version is %u.\n", version_major);
    printf("Minor version is %u.\n", version_minor);
    if ((info & 0x40000000) == 0) {
        DWORD build = platform;
        printf("Build is %u.\n", build);
    }
    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computer_name);
    GetComputerNameA(computer_name, &size);
    printf("Computer Name: %s", computer_name);

    return 0;

    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers=input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    double min,max;
    find_minmax(numbers,min,max);

    const auto bins = make_histogram(numbers, bin_count,min,max);
    show_histogram_svg(bins);
    return 0;
}
