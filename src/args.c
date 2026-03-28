#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "../include/args.h"

programConfig handle_args(int argc, char* argv[]) {
    int8_t opt;
    programConfig cfg = {PYTHON, TXT};

    struct option long_options[] = {
        {"shell", required_argument, NULL, 's'},
        {"output", required_argument, NULL, 'o'},
        {"version", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0}
    };

    do {
        opt = getopt_long(argc, argv, "s:o:vh", long_options, NULL);
        switch(opt) {
            case 's': 
                if (!strcmp(optarg, "python3")) cfg.shell = PYTHON;
                else if (!strcmp(optarg, "pyspark")) cfg.shell = PYSPARK;
                else goto INVALID_SHELL; 
                break;

            case 'o': 
                if(!strcmp(optarg, "txt")) cfg.output = TXT;
                else if(!strcmp(optarg, "notebook")) cfg.output = NOTEBOOK;
                else if(!strcmp(optarg, "markdown")) cfg.output = MARKDOWN;
                else goto INVALID_OUTPUT; 
                break;
                
            case 'v':
                print_version();
                exit(EXIT_SUCCESS);

            case 'h': 
                print_help();
                exit(EXIT_SUCCESS);

            case -1 : break;
            case '?':
            default: goto INVALID_ARGUMENT;
        }
    } while (opt != -1);
    return cfg;

INVALID_ARGUMENT:
    fprintf(stderr, "Invalid argument provided\n\n");
    print_help();
    exit(EXIT_FAILURE);

INVALID_OUTPUT:     
    fprintf(stderr, 
        "Invalid output\n"
        "Valid options: [txt, notebook, markdown]\n");
    exit(EXIT_FAILURE);

INVALID_SHELL:      
    fprintf(stderr,
        "Invalid shell type.\n"
        "Valid options: [python3, pyspark]\n"); 
    exit(EXIT_FAILURE);
}

void print_version() {
    fprintf(stdout,
        "pyNoteParser version 0.0.1\n"
        "Written by Desan Silva\n"
    );
}

void print_help() {
    fprintf(stdout,
        "Usage: pyNoteParser [OPTIONS]...\n"
        "\n"
        "Run a Python or PySpark terminal session and log the output\n"
        "\n"
        "Options:\n"
        "  -s, --shell <type>     Select shell type to run (python3, pyspark)\n"
        "                         (default = python3)\n"
        "  -o, --output <format>  Set output format for logs (txt, notebook, markdown)\n"
        "                         (default = txt)\n"
        "  -v, --version          output version information and exit\n"
        "  -h, --help             display this help and exit\n"
        "\n"
        "Examples:\n"
        "  pyNoteParser --shell python --output txt\n"
        "  pyNoteParser -s pyspark -o markdown\n"
        "\n"
    );
}
