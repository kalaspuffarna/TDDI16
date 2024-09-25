#include "image.h"
#include "window.h"
#include "load.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

/**
 * Class that stores a summary of an image.
 *
 * This summary is intended to contain a high-level representation of the
 * important parts of an image. I.e. it shall contain what a human eye would
 * find relevant, while ignoring things that the human eye would find
 * irrelevant.
 *
 * To approximate human perception, we store a series of booleans that indicate
 * if the brightness of the image has increased or not. We do this for all
 * horizontal lines and vertical lines in a downsampled version of the image.
 *
 * See the lab instructions for more details.
 *
 * Note: You will need to use this data structure as the key in a hash table. As
 * such, you will need to implement equality checks and a hash function for this
 * data structure.
 */

// How small shall we make the images before comparing them?
const size_t image_size = 32;
const size_t summary_size = 31;
const int tolerance = 1;
int equal_calls{};

class Image_Summary
{
public:
    // Horizontal increases in brightness.
    vector<bool> horizontal;

    // Vertical increases in brightness.
    vector<bool> vertical;

    bool operator==(const Image_Summary &other) const
    {
        int diff{};
        for(int i{}; i < summary_size; i++)
        {
            if(horizontal.at(i) != other.horizontal.at(i))diff++;
            if(horizontal.at(i) != other.horizontal.at(i))diff++;
        }
        return diff <= tolerance;
    }
};

namespace std
{
    template <>
    struct hash<Image_Summary>
    {
        size_t operator()(const Image_Summary &summary) const
        {
            size_t h1 = hash<vector<bool>>{}(summary.horizontal);
            size_t h2 = hash<vector<bool>>{}(summary.vertical);
            return h1 ^ (h2 << 1);
        }
        //vi måste på något sätt manipulera jämnförelsen som sker mellan hasher
    };
}


Image_Summary compute_summary(const Image &image)
{
    Image_Summary result;

    // Precompute the brightness values and store them in a vector
    std::vector<std::vector<double>> brightness_matrix(summary_size + 1, std::vector<double>(summary_size + 1));
    //double a_bright = image.average_brightness();

    for (size_t y = 0; y < summary_size + 1; y++)
    {
        for (size_t x = 0; x < summary_size + 1; x++)
        {
            brightness_matrix[y][x] = image.pixel(x, y).brightness() /* a_bright*/;
        }
    }

    // Compute horizontal and vertical brightness increases
    for (size_t y = 0; y < summary_size; y++)
    {
        for (size_t x = 0; x < summary_size; x++)
        {
            result.horizontal.emplace_back(brightness_matrix[y][x] >= brightness_matrix[y][x + 1]);
            result.vertical.emplace_back(brightness_matrix[y][x] >= brightness_matrix[y + 1][x]);
        }
    }
    // TODO: Finish the implementation.
    // The lines below are here to avoid warnings. They can be removed.
    // se till att vi fixar avragebrightness på bilden.
    (void)image;
    (void)summary_size;

    return result;
}

bool find(std::unordered_map<Image_Summary, vector<string>> const & map, Image_Summary const & is)
{
    for(auto e : map)
    {
        if(e.first == is) return true;
    }
    return false;
}

int main(int argc, const char *argv[])
{

    WindowPtr window = Window::create(argc, argv);

    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " [--nopause] [--nowindow] <directory>" << endl;
        cerr << "Missing directory containing files!" << endl;
        return 1;
    }

    vector<string> files = list_files(argv[1], ".jpg");
    cout << "Found " << files.size() << " image files." << endl;

    if (files.size() <= 0)
    {
        cerr << "No files found! Make sure you entered a proper path!" << endl;
        return 1;
    }

    auto begin = std::chrono::high_resolution_clock::now();
    std::unordered_map<Image_Summary, vector<string>> id_names{};
    std::unordered_set<Image_Summary> duplicates{};

    for (const auto &file : files)
    {
        auto id{compute_summary(load_image(file).shrink(image_size, image_size))};
        //if (id_names.find(id) != id_names.end()) //här är problemet, vi måste få in threshold skillnad i find
        if(find(id_names, id))
        {
            duplicates.insert(id);
        }
        id_names[id].push_back(file);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    cout << "Total time: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;
    for (auto d : duplicates)
    {
        cout << "------------matching-------------" << std::endl;
        for (int i{}; i < id_names[d].size(); i++)
        {
            cout << "file-name: " << id_names[d].at(i) << std::endl;
        }
        cout << "---------------------------------" << std::endl;
    }

    /**
     * TODO:
     * - Display sets of files with equal summaries
     */

    return 0;
}
