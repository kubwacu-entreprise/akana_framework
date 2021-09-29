#include <regex>
#include <map>
#include <fstream>
#include <sys/stat.h>
#include "utils.h"
#include "commands.h"

bool Utils::name_isvalid(const string &name){
    if(regex_match(name, regex("^[a-z]*[a-z0-9_]*[a-z0-9]+$")) && name.length() <= 50) return true;
    else return false;
    
}

bool Utils::folder_exist(const string &file){
    struct stat info;
    return (stat(file.c_str(), &info) == 0);
}

bool Utils::gen_project_struct(const string &project_name){
    map<string, string> project_structure = {
        // framework files
        {project_name + "/src/database.php", "bin/framework/database"},
        {project_name + "/src/errors_manager.php", "bin/framework/errors_manager"},
        {project_name + "/src/exceptions.php", "bin/framework/exceptions"},
        {project_name + "/src/main.php", "bin/framework/main"},
        {project_name + "/src/model.php", "bin/framework/model"},
        {project_name + "/src/response.php", "bin/framework/response"},
        {project_name + "/src/serializer.php", "bin/framework/serializer"},
        {project_name + "/src/status.php", "bin/framework/status"},
        {project_name + "/src/utils.php", "bin/framework/utils"},

        // home file
        {project_name + "/src/html/home.php", "bin/home/home"},

        // main file
        {project_name + "/start/index.php", "bin/main/index"},

        // config files
        {project_name + "/config.php", "bin/configuration/config"},
        {project_name + "/env.php", "bin/configuration/env"},
        {project_name + "/root.php", "bin/configuration/root"},   
    };

    system(string("mkdir " + project_name + "\\res").c_str());
    system(string("mkdir " + project_name + "\\src\\html").c_str());
    system(string("mkdir " + project_name + "\\start").c_str());

    //  get akana location in environment variables 
    char* t = getenv("akana");
    string akana_location = t == NULL ? "" : string(t) + "/";
    
    for (pair<string, string> el: project_structure) {
        // create the project file in append mode 
        ofstream file(el.first.c_str(), ios::app);
        
        // open the file to copy 
        ifstream file_copy((akana_location + el.second).c_str());
        if(file_copy){
            string line;
            while(getline(file_copy, line)){
                //  copy the content of the framework file in the file for the project 
                file << line + "\n";
            }
        }

        //  if there was error occured while opening the file to copy 
        else{
            cout << endl << "There was error while opening file '" << el.second << "' to copy it in '" << el.first << "'." << endl;
            return false;
        }

        //  print the name of the created project file to notice the developper 
        cout << el.first << endl;
    }

    return true;
}

bool Utils::gen_resource_struct(const string &resource_name){
    map<string, string> resource_structure = {
        {"res" + resource_name + "/controllers.php", "bin/resource/controllers"},
        {"res" + resource_name + "/endpoints.php", "bin/resource/endpoints"},
        {"res" + resource_name + "/models.php", "bin/resource/models"},
        {"res" + resource_name + "/serializers.php", "bin/resource/serializers"},
    };

    //  get akana location in environment variables 
    char* t = getenv("akana");
    string akana_location = t == NULL ? "" : string(t) + "/";
    
    for (pair<string, string> el: resource_structure) {
        //  create the resource file in append mode 
        ofstream file(el.first.c_str(), ios::app);
        
        //  open thee file to copy 
        ifstream file_copy((akana_location + el.second).c_str());
        if(file_copy){
            string line;
            while(getline(file_copy, line)){
                //  copy the content of the framework file in the file for the resource 
                file << line + "\n";
            }
        }

        //  if there was error occured while opening the file to copy 
        else{
            cout << endl << "There was error while opening file '" << el.second << "' to copy it in '" << el.first << "'." << endl;
            return false;
        }

        //  print the name of the created resource file to notice the developper 
        cout << el.first << endl;
    }

    return true;
}

void Utils::create_file(const string &file){
    ofstream fichier(file.c_str());
}

vector<string> Utils::get_commands(){
    vector<string> commands;

    commands.push_back("create-project");
    commands.push_back("add-resource");
    commands.push_back("runserver");
    commands.push_back("about");
    commands.push_back("version");
    commands.push_back("help");

    return commands;
}

bool Utils::command_isvalid(string command){
    vector<string> valid_commands = Utils::get_commands();
    
    for(int i=0; i<valid_commands.size(); i++){
        if(command == valid_commands[i])
            return true;
    }

    return false;
}

void Utils::execute_command(string command, int arguments_length, char* arguments[]){
    if(command == "create-project"){
        if(arguments_length > 2){
            string project_name = arguments[2];
            Commands::create_project(project_name);
        }

        else{
            cout << "Command 'create-project' requires a parameter for the project name." << endl;
            cout << endl << "Usage: akana create-project <project_name>." << endl;
            cout << endl;
        }
        
    }

    else if(command == "add-resource"){
        if(arguments_length > 2){
            string resource_name = arguments[2];
            Commands::add_resource(resource_name);
        }
        
        else{
            cout << "Command 'add-resource' requires a parameter for the resource name." << endl;
            cout << endl << "Usage: akana add-resource <resource_name>." << endl;
            cout << endl;
        }
    }

    else if(command == "runserver"){
        Commands::runserver();
    }

    else if(command == "help"){
        Commands::help();
    }

    else if(command == "about"){
        Commands::about();
    }
}

void Utils::get_name_rules(){
    cout << "- It must start with a letter." << endl;
    cout << "- It must end with a letter or a number." << endl;
    cout << "- It must contain only lowercase letters." << endl;
    cout << "- All special characters are not allowed except underscore '_'." << endl;
    cout << "- Maximum length is 50 characters." << endl;
}