#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <iostream>
#include <yaml-cpp/yaml.h>

#include <yaml.h>
#include <libfyaml.h>
#include <fstream>

#include <catch2/catch_all.hpp>

const char * yaml_file = "sample_yaml_file_download_for_testing.yaml";

TEST_CASE("yaml-cpp"){
    BENCHMARK_ADVANCED("deserialization_yaml-cpp")(Catch::Benchmark::Chronometer meter){//из битов в норм файл
        meter.measure([] {
            YAML::Node Norm_File = YAML::LoadFile(yaml_file);
        });
    };
    BENCHMARK_ADVANCED("serialization_yaml-cpp")(Catch::Benchmark::Chronometer meter){//из норм файла в биты
            YAML::Node Norm_File = YAML::LoadFile(yaml_file);
            meter.measure([&Norm_File] {
                std::ofstream ss(yaml_file);
                ss<<Norm_File;
            });
        };
}

TEST_CASE("libfyaml"){
    BENCHMARK_ADVANCED("deserialization_lybfyaml")(Catch::Benchmark::Chronometer meter){
        //FILE *file;
        //file = fopen(yaml_file, "wb");//как двоичный открываем
        meter.measure([] {
            fy_document* doc = fy_document_build_from_file(NULL, yaml_file);
            fy_document_destroy(doc);
        });

        //std::ifstream File;
        //File.open(yaml_file);
        //std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(File), {});
        

    };
    BENCHMARK_ADVANCED("serialization_lybfyaml")(Catch::Benchmark::Chronometer meter){
            fy_document* doc = fy_document_build_from_file(NULL, yaml_file);
            FILE *file;
            file = fopen("output.yaml", "wb");//как двоичный открываем
            meter.measure([&doc, &file] {
                fy_emit_document_to_fp(doc, FYECF_DEFAULT, file);
                //fy_document_build_from_file(NULL, yaml_file);
            });
            fclose(file);

            //std::ifstream File;
            //File.open(yaml_file);
            //std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(File), {});


        };
}
TEST_CASE("libyaml"){
    BENCHMARK_ADVANCED("deserialization_lybyaml")(Catch::Benchmark::Chronometer meter){
            FILE* file;
            file = fopen (yaml_file, "rb");
            meter.measure([&file] {
                yaml_parser_t parser;
                yaml_parser_initialize(&parser);
                yaml_parser_set_input_file(&parser, file);
                yaml_document_t doc;
                yaml_parser_load (&parser, &doc);
                yaml_document_delete(&doc);
                yaml_parser_delete(&parser);

            });
            fclose(file);


        };
    BENCHMARK_ADVANCED("serialization_lybyaml")(Catch::Benchmark::Chronometer meter){
            FILE* file;
            file = fopen (yaml_file, "rb");
            yaml_parser_t parser;
            yaml_parser_initialize(&parser);
            yaml_parser_set_input_file(&parser, file);
            yaml_document_t doc;
            yaml_parser_load (&parser, &doc);
            yaml_parser_delete(&parser);
            fclose(file);
            file = fopen("output.yaml", "w");
            meter.measure([&doc, &file] {
                yaml_emitter_t emitter;
                yaml_emitter_initialize(&emitter);
                yaml_emitter_set_output_file(&emitter, file);
                yaml_emitter_dump(&emitter,&doc);
                yaml_emitter_close(&emitter);

            });
            yaml_document_delete(&doc);
            fclose(file);


        };
}


//load - deserialization, save - se

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
