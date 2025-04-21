#include <vector>
#include <string>
#define SMOOTHING_DATA_WINDOW 166
#define MIN_AVERAGE_WINDOW_WIDTH 5

class solution
{
    private:
        std::vector<double> xvalues;
        std::vector<double> yvalues;
        std::vector<double> filtered_yvalues;
        void jump_event(int event_index, int window_size); 
    public:
        void parse_data(std::string path);
        void apply_filter(int window_size);
        void check_deltas(int jump_event_delta, int window_size);
        void plot_data(std::string filename);
};
