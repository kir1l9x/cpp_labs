#include "../lib/work_with_comm_args/ArgParsing.h"
#include "../lib/work_with_output_bmp/BMP_Output.h"
#include <chrono>


int main(int argc, char* argv[]) {
    for (int i = 1; i < 100; ++i) {
        SandPileParameters sand_parameters{};
        Arguments command_arguments = Parse(argc, argv);
        sand_parameters.SetSize(command_arguments.input_file);
        sand_parameters.StartSandPile();
        sand_parameters.ReadFromTSV(command_arguments.input_file);
        uint64_t iterations = 0;
        sand_parameters.SetHowMany(i);
        if (command_arguments.frequency == 0 && command_arguments.max_iterations == 0xFFFFFFFFFFFFFFFF) {
            sand_parameters.FastToppleAll();
            WriteToBMP(sand_parameters, command_arguments.output_dir, iterations);
        }
    }
    /*while (!sand_parameters.IsStable() && iterations <= command_arguments.max_iterations) {
        if (command_arguments.frequency != 0 && iterations % command_arguments.frequency == 0) {
            WriteToBMP(sand_parameters, command_arguments.output_dir, iterations);
        }
        sand_parameters.ToppleAllOnce();
        ++iterations;
    }*/
    //WriteToBMP(sand_parameters, command_arguments.output_dir, iterations);
    std::ranges::reverse
    std::reverse()
    std::transform()
    return 0;
}
