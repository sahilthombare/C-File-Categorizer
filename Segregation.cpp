/*
    movie -> { "avi", "mp4", "mkv", "wmv", "mov", "flv", "mpeg", "mpg", "rm", "rmvb", "m4v" }
    audio -> { "mp3", "wav", "flac", "aac", "ogg", "wma", "m4a", "aiff", "ape", "alac" }
    image -> { "jpg", "jpeg", "png", "gif", "bmp", "tiff", "webp", "svg", "ico" }
    Document -> { "pdf", "doc", "docx", "ppt", "pptx", "xls", "xlsx", "odt", "odp", "ods", "txt", "rtf" }
    compress -> { "zip", "rar", "7z", "tar", "gz", "xz", "bz2", "tar.gz", "tar.xz", "tar.bz2" }
    Developer -> { "cpp", "h", "java", "py", "html", "css", "js", "php", "xml", "json", "md", "txt", "rb", "swift", "c", "cs", "go", "sql", "sh", "yaml", "toml" }
    web file ->{ "html", "css", "js", "php", "asp", "jsp", "xml", "json", "svg", "ico", "woff", "woff2", "ttf", "eot" }

*/
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <cstring>
#include <map>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;


/*
    Singly linkedlist + vector
    store extension in vector 
*/
class  Singly_linkedlist {

    public :

    vector <string> all_extension;
    string str;
    Singly_linkedlist *next_ptr;

    Singly_linkedlist()
    {
        str.clear();
        next_ptr = NULL;
    }

    Singly_linkedlist(vector <string> &Extension,string str)
    {
        for(auto name : Extension)
        {
            all_extension.push_back(name);
        }
        this -> str = str; 
    }

};

class Segregation
{

    public:
        Singly_linkedlist *first_node;
        string directory_path;
        vector <string> directory_directory;
        map<string,vector<string>> directory_file_extension;


        Segregation()
        {
            first_node = NULL;
            directory_path.clear();
        }
        
    void store_extension( vector <string> &Extension,string Directory_name){
        
        Singly_linkedlist *create_new_node = new Singly_linkedlist(Extension,Directory_name);

        if(create_new_node == NULL)
        {
            cout << "Memory allocation failed" << endl;
            return;
        }

        if(first_node == NULL)
        {
            first_node = create_new_node;
            return;
        }

        create_new_node -> next_ptr = first_node;
        first_node = create_new_node;

        return;
    }

    void Display_store_extension()
    {
        Singly_linkedlist *current_node = first_node;

        while(current_node != NULL)
        {
            for(string name : current_node -> all_extension)
            {
                cout << name << "  ";
            }
            cout << " Directory : " << current_node ->str << endl;

            current_node = current_node -> next_ptr;
        }
    }

    void input_directory_path()
    {
        cout << "ENTER DIRECTORY PATH :" << "   ";
        cin >> directory_path;
        return;
    } 

    bool check_directory_present(const string& path) {
        DIR* directory = opendir(path.c_str());
        if (directory) 
        {   
            closedir(directory);
            return true;
        }
            return false;
    }

    bool check_folder()
    {
        if(check_directory_present(directory_path))
        {
            cout << "Given path is directory" << endl;
            return true;
        }
        else 
        {
            cout << "Given path is not directory" << endl;
            return false;
        }
    }

    bool check_file_present()
    {
        int i_count = 0;
        DIR* folder = opendir(directory_path.c_str());
        if(folder)
        {
            struct dirent *entry;

                while ((entry = readdir(folder)) != NULL) 
                {
                    if (entry->d_type == DT_REG)
                    { 
                        i_count++;
                    }
                } 

                closedir(folder);  
        }

        if(i_count > 0)
        {
            cout << "files exist in given path" << endl;
            return true;
        }
        else
        {
            cout << "files does not exist in path" << endl;
            return false;
        }
    }

    void store_directory_extension_file(){

        string file_name;
        string file_extension;

        DIR* folder = opendir(directory_path.c_str());
        if(folder)
        {
            struct dirent *entry;
            while ((entry = readdir(folder)))
            {
                if(entry -> d_type == DT_REG)
                {
                    file_name = entry -> d_name;
                    file_extension = file_name.substr(file_name.rfind('.') + 1);
                    if(!file_extension.empty())
                    {
                        directory_file_extension[file_extension].push_back(directory_path + '/' + file_name);
                    }

                }
            }
            closedir(folder);   
        }
    }

    void Display_directory_file_extension(){
        for( auto& extension : directory_file_extension){
            cout << "Extension :" << extension.first << endl;
            vector<string> &v = extension.second;

            for( auto &path : v){
                cout << path << endl;
            }
        }
    }

    bool check_directory_in_path(string foldar_name)
    {
        bool found = false;
        DIR *folder = opendir(directory_path.c_str());
        if(folder == nullptr){
            cout << "Failed to open folder" << endl;
            return false;
        }
        struct dirent* entry;
        while ((entry = readdir(folder)) != nullptr) {
            if(entry ->d_type == DT_DIR){
            if (string(entry->d_name) != "." && string(entry->d_name) != "..") {
                if(entry->d_name == foldar_name)
                {
                    found = true;
                    break;
                } 
            }
            }
        }
        closedir(folder);
        
        return found;
        
    }

    void folder_create()
    {
        Singly_linkedlist *current_node = first_node;
        if(current_node == NULL)
        {
            cout << "Singly linkedlist is empty" << endl;
        }
        string foldar_name ;
        string filename;
        string source;
        string destination;
        for(auto &extension : directory_file_extension)
        {
            if(current_node == NULL){
                cout << "NULL" << endl;
            }

            while(current_node != NULL)
            {  
                foldar_name.clear();
                vector <string> &v_extension = current_node -> all_extension;
                for(const auto &name : v_extension)
                {
                    if(extension.first == name)
                    {
                        foldar_name = current_node -> str;
                        break;
                    }
                }
                if(!foldar_name.empty())
                {
                    break;
                }
                
                current_node = current_node -> next_ptr;
            }
            if(current_node == NULL){
                foldar_name = "other_file";
            }
            if(!foldar_name.empty())
            {
                if(!check_directory_in_path(foldar_name))
                {
                   
                    filename = directory_path + "/" + foldar_name;
                    vector<string> &v = extension.second;

                   if(mkdir(filename.c_str(),0777) == 0)
                    {
                        for(const auto &path : v){
                            destination = (path.substr(path.rfind('/') + 1));
                            source = filename + "/" + destination;
                            rename(path.c_str(),source.c_str());
                        }    
                    }
                    else
                    {
                        cout << "folder create failed" << endl;
                    }
                }
                else{
                    filename = directory_path + "/" + foldar_name;
                 
                    vector<string> &v = extension.second;
                     for(const auto &path : v){
                         destination = (path.substr(path.rfind('/') + 1));
                            source = filename + "/" + destination;
                           
                            rename(path.c_str(),source.c_str());
                    }
                }
                
            }
            current_node = first_node;

        }
    }

    void create_folder_inside(){
        
        string file_name;
        string source;
        string destination;
        string path_name;
        string folder_path;
        string file_extension;
        DIR* directory = opendir(directory_path.c_str());
        if(directory == nullptr){
            cout << "Failed to open folder" << endl;
            return ;
        }
    
            struct dirent* entry;
            while ((entry = readdir(directory)) != nullptr) 
            {
                if(entry ->d_type == DT_DIR)
                {
                    if (string(entry->d_name) != "." && string(entry->d_name) != "..") 
                    {
                        directory_directory.push_back(entry -> d_name);
      
                    }
                }
            }
            closedir(directory);
        }
    
    void Display_directory(){
        for(auto& directory : directory_directory){
            cout << directory << endl;
        }
    }

    bool folder_found(string name,string take_path){
     
        bool found = false;
        DIR *folder = opendir(take_path.c_str());
        if(folder == nullptr){
            cout << "Failed to open folder" << endl;
            return false;
        }
        struct dirent* entry;
        while ((entry = readdir(folder)) != nullptr) {
            if(entry ->d_type == DT_DIR){
            if (string(entry->d_name) != "." && string(entry->d_name) != "..") {
          
                if(entry->d_name == name)
                {
          
                    found = true;
                    break;
                } 
            }
            }
        }
        closedir(folder);
     
        return found;
    }

    void Directory_create_inside(){
        string take_path;
        string file_name;
        string make;
        string destination;
        string file_extension;
        string source;
        map<string,vector<string>> m_make;
        for(auto& directory: directory_directory){
            take_path = directory_path + "/" + directory;
            
      
            DIR* folder = opendir(take_path.c_str());
            if(folder == nullptr)
            {
                cout<< "Directory open failed" << endl;
                return;
            }
            if(folder)
            {
                struct dirent *entry;
                while ((entry = readdir(folder)))
                {
                    if(entry -> d_type == DT_REG)
                    {
                        file_name = entry -> d_name;
                        file_extension = file_name.substr(file_name.rfind('.') + 1);
                        if(!file_extension.empty())
                        {
                            m_make[file_extension].push_back(take_path + '/' + file_name);
                    
                        }

                    }
                }
                closedir(folder);

                for(auto& map :m_make)
                {
                    if(!folder_found(map.first,take_path))
                    {
                        make = take_path + "/" + map.first;
                   
                        if(mkdir(make.c_str(),0777) == 0)
                        {
                            vector<string> &v = map.second;
                            for(const auto &path : v)
                            {
                                destination = (path.substr(path.rfind('/') + 1));
                              

                                source = make + "/" + destination;

                            
                                rename(path.c_str(),source.c_str());
                            }
                        }
                        else{
                            cout << "Failed to create folder" << endl;
                        }
                    }
                    else{
                        make = take_path + "/" + map.first;
                        vector<string> &v = map.second;
                        for(const auto &path : v)
                        {
                            destination = (path.substr(path.rfind('/') + 1));
                            source = make + "/" + destination;
                            rename(path.c_str(),source.c_str());
                        }
                        
                    }
                }
            }   
            m_make.clear();
        }
    }
    

};

int main()
{
    bool b_ret;
    Segregation Segregation_obj;
    vector <string> v = {"log","msg","odt","pages","rtf","tex","txt","wpd","wps", "pdf", "doc", "docx","xls", "xlsx", "odp", "ods" };
    Segregation_obj.store_extension(v,"Documents_file");
    v.clear();
    v = {"ppt", "pptx",};
    Segregation_obj.store_extension(v,"Presentation_file");
    v = { "dat", "gbr", "ged", "key", "keychain", "pps",  "sdf", "tar", "tax2012", "vcf", "xml"};
    Segregation_obj.store_extension(v,"Data_File");
    v.clear();
    v = {"aif", "iff", "m3u", "mid", "mp3", "mpa", "ra", "wav", "wma", "mp3", "wav", "flac", "aac", "ogg", "wma", "m4a", "aiff", "ape", "alac" };
    Segregation_obj.store_extension(v,"Audio_file");
    v.clear();
    v = {"3g2", "3gp", "asf", "asx", "avi", "flv", "m4v", "mov", "mpg", "rm", "srt", "swf", "vob", "wmv", "avi", "mp4", "mkv", "wmv", "mov","mpeg", "rmvb" };
    Segregation_obj.store_extension(v,"Video");
    v.clear();
    v = {"3dm", "3ds", "max", "obj"};
    Segregation_obj.store_extension(v,"3D_image_files");
    v.clear();
    v = {"bmp", "dds", "gif", "jpg","jpeg", "png", "psd", "pspimage", "tga", "thm", "tif", "tiff", "yuv","ai", "eps", "ps", "svg"};
    Segregation_obj.store_extension(v,"image_file");
    v.clear();
    v = {"indd", "pct", "pub", "qxd", "sla"};
    Segregation_obj.store_extension(v,"Design&Graphics");
    v.clear();
    v = {"xlr", "xlsx", "xls", "ods", "csv" };

    Segregation_obj.store_extension(v,"Table_file");
    v.clear();
    v = {"accdb", "db", "dbf", "mdb", "pdb", "sql"};
    Segregation_obj.store_extension(v,"Database_file");
    v.clear();
    v = {"apk", "app", "bat", "cgi", "com", "exe", "gadget", "jar", "pif", "vb", "wsf"};
    Segregation_obj.store_extension(v,"Executable_file");
    v.clear();
    v = {"dem", "gam", "nes", "rom", "sav"};
    Segregation_obj.store_extension(v,"Game_file");
    v.clear();
    v = {"dwg", "dxf"};
    Segregation_obj.store_extension(v,"CAD_file");
    v.clear();
    v = {"gpx", "kml", "kmz"};
    Segregation_obj.store_extension(v,"GIS_file");
    v.clear();
    v = {"asp", "aspx", "cer", "cfm", "csr", "css", "htm", "html","json" ,"js", "jsp", "php", "rss", "xhtml"};
    Segregation_obj.store_extension(v,"Web_file");
    v.clear();
    v = {"crx", "plugin"};
    Segregation_obj.store_extension(v,"Plugin_files");
    v.clear();
    v = {"fnt", "fon", "otf", "ttf"};
    Segregation_obj.store_extension(v,"Font_file");
    v.clear(); 
    v = {"hqx", "mim", "uue"};
    Segregation_obj.store_extension(v,"Encoding_file");
    v.clear();
    v = {"7z", "cbr", "deb","bz2","BetterMeApk" ,"BetterMeApk(1)","gz","a", "pkg", "rar", "rpm", "sitx", "tar.gz", "zip", "zipx"};
    Segregation_obj.store_extension(v,"Compressed_file");
    v.clear();
    v = {"bin", "cue", "dmg", "iso", "mdf", "toast", "vcd"};
    Segregation_obj.store_extension(v,"Disk_image_file");
    v.clear();
    v = {"c", "class", "cpp", "cs", "dtd", "fla", "h", "java", "lua", "m", "pl", "py", "sh", "sln","go","rb", "swift", "vcxproj", "yaml","toml","xcodeproj"};
    Segregation_obj.store_extension(v,"Developer_file");
    v.clear();
    v = {"bak", "tmp"};
    Segregation_obj.store_extension(v,"Backup_file");
    v.clear();
    v = {"crdownload", "ics", "msi", "part", "torrent"};
    Segregation_obj.store_extension(v,"torrent_windows_file");
    v.clear();
    v = {"patch"};
    Segregation_obj.store_extension(v,"Patch");
   
   
    Segregation_obj.input_directory_path();
    b_ret = Segregation_obj.check_folder();
    if(true == b_ret)
    {
        b_ret = Segregation_obj.check_file_present();
        if(true == b_ret)
        {
            Segregation_obj.store_directory_extension_file();
            Segregation_obj.folder_create();
          
        }
    }
    Segregation_obj.create_folder_inside();
    Segregation_obj.Directory_create_inside();
   
    return 0;

}
