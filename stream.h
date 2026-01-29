//Abdullah Ali Khan, CS163- in person, 11/14/2025,
//This file contains all the struct and classes

#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int SIZE = 101;
struct stream 
{
    char * stream_id;
    char * name;
    char * game;
    int  viewers;
    int  duration;
    char *language;
    char *region;
    char *category;
    char *start_time;
};


struct node 
{
    stream data;
    node * next;
};


class table 
{
public:
    table(int SIZE);               
    ~table();                            
    int insert(stream & to_add); 
    int load_from_file(const char * filename);
    int display_by_name (const char * name);
    int retrieve(const char * name, stream *&match , int &count, int max);
    int display_all(); 
    int remove_by_name(const char *name);  
    int display_by_game(const char *game);
    int insert_with_collision_count(stream& to_add, int& collisions, bool use_second_hash);


private:
    int hash_function(const char * key);
    int hash_function2(const char * key);
    node ** hash_table;
    int table_size;
    int display_all_recursive(int index, node* current);
};



