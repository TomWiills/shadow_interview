#include <vector>
#include <string>
#include <filesystem>
#define SMOOTHING_DATA_WINDOW 166

class solution
{
    public:
        solution()
        {
            std::filesystem::create_directories(plot_dir);
        };
        std::string plot_dir = "output/plots/";
        void parse_data(std::string path);
        void apply_filter(int window_size);
        void check_deltas(int jump_event_delta, int window_size);
        void plot_data(std::string filename) const;
        void set_xValues(std::vector<double> x_values){xvalues = x_values;};
        void set_yValues(std::vector<double> y_values){yvalues = y_values;};
        void set_filtered_yValues(std::vector<double> filtered_y_values){filtered_yvalues = filtered_y_values;};
        std::vector<double> get_xValues(void){return xvalues;};
        std::vector<double> get_yValues(void){return yvalues;};
        std::vector<double> get_filtered_yValues(void){return filtered_yvalues;};
    private:
        std::vector<double> xvalues;
        std::vector<double> yvalues;
        std::vector<double> filtered_yvalues;
        void jump_event(int event_index, int window_size); 
    
};
