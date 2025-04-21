#include <solution.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <matplotlibcpp.h>

//function retrieve data from txt file
void solution::parse_data(std::string path)
{
    std::ifstream file(path); 
    if (!file) 
    {
        throw std::ios_base::failure("Error opening the file!");
    }

    std::string line;
    //skip first line as it contains column titles
    std::getline(file, line);

    while(std::getline(file, line))
    {
        std::istringstream ss(line);
        double x, y;
        
        if (ss >> x >> y) {
            xvalues.push_back(x);
            yvalues.push_back(y);
        }
        else
        {
            std::cout << "Line of data is not formatted correctly, skipping..." << std::endl;
        }
    }
};

//function applies average window filter to y values
void solution::apply_filter(int window_size)
{
    int size = yvalues.size();
    filtered_yvalues = yvalues;
    double sum = 0.0;
    int left = 0;
    int right = std::min(window_size -1, size -1);

    if(window_size == 1){
        return;
    }

    for(int i = left; i <= right; ++i) 
    {
        sum += yvalues[i];
    }

    for(int i = 0; i < size; ++i) 
    {
        filtered_yvalues[i] = (sum / (right - left + 1));

        //ensure the last few data points are not raw and are still averaged using the minimum of window_size/2
        if(left < right - window_size/2)
        {
            sum -= yvalues[left];
            left++;
        }

        if(right < size -1)
        {
            sum += yvalues[right +1];
            right++;
        }
    }
};

//function for checking for the delta threshhold 
void solution::check_deltas(int jump_event_delta, int window_size)
{
    double delta;
    for(int i = 1; i < static_cast<int>(yvalues.size()); i++)
    {
        delta = yvalues[i] - yvalues[i-1];
        if(delta > jump_event_delta || delta < -jump_event_delta)
        {
            jump_event(i, window_size);
        }
    }
};

// Function for smoothing in a given window
void solution::jump_event(int event_index, int window_size)
{
    int endofvector = yvalues.size();
    int startIdx = std::max(0, event_index - SMOOTHING_DATA_WINDOW);
    int endIdx = std::min(endofvector - 1, event_index + SMOOTHING_DATA_WINDOW);
    
    // need to create a tmp or the smoothing will effect the averages as it goes
    std::vector<double> temp = filtered_yvalues;

    for (int i = startIdx; i <= endIdx; ++i) {
        double sum = 0.0;
        int count = 0;

        for (int j = std::max(0, i - window_size); j <= std::min(endofvector - 1, i + window_size); ++j) {
            sum += temp[j];
            ++count;
        }

        filtered_yvalues[i] = sum / count;
    }
}

void solution::plot_data(std::string filename) const
{
    matplotlibcpp::named_plot("Raw Data", xvalues, yvalues);
    matplotlibcpp::named_plot("Filtered Data", xvalues, filtered_yvalues);
    matplotlibcpp::legend();
    matplotlibcpp::save(plot_dir + filename);
    std::cout << "Find plot file here: " + plot_dir + filename + ".png"<< std::endl;
};

#ifndef UNIT_TESTING
int main()
{
    int filter_window_size = 60;
    int jump_event_filter = 1;
    solution sl;

    sl.parse_data("../data/sample.txt");
    sl.apply_filter(filter_window_size);
    sl.check_deltas(jump_event_filter, filter_window_size);
    sl.plot_data("solution_comparison");
}
#endif