//Abdullah Ali Khan, CS163- in person, 11/14/2025
// this file declares all the fuctions

#include "stream.h"
#include <fstream>

int compare_nocase(const char a[], const char b[])
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        char ca = tolower(a[i]);
        char cb = tolower(b[i]);
        if (ca < cb) return -1;
        if (ca > cb) return 1;
        ++i;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    if (a[i] == '\0') return -1;
    return 1;
}

table::table(int SIZE)
{
    table_size = SIZE;
    hash_table = new node*[table_size];

    for (int i = 0; i < table_size; ++i)
        hash_table[i] = nullptr;
}

int table::hash_function(const char * key)
{
    int hash = 0;

    for (int i = 0; key[i] != '\0'; ++i) {
        hash = (hash * 31 + tolower(key[i])) % table_size;
    }
    return hash;
}

int table::hash_function2(const char * key)
{
	
    int hash = 0;

    for (int i = 0; key[i] != '\0'; ++i) {
        hash = (hash * 17 + tolower(key[i]) * 7) % table_size;
    }

    return hash;
}

// Inserts a stream into the hash table. If a collision occurs (two streams
// hash to the same index), increment the collisions counter.
// use_second_hash: if true, uses the second hash function to compute index
int table::insert_with_collision_count(stream& to_add, int& collisions, bool use_second_hash)
{
    int index;

    if (use_second_hash)
        index = hash_function2(to_add.name);
    else
        index = hash_function(to_add.name);

    if (hash_table[index] != nullptr)
        collisions++;  

    node* new_node = new node;
    new_node->data = to_add;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;

    return index;
}


int table::insert(stream & to_add) {
    int index = hash_function(to_add.name);

    node * new_node = new node;
    new_node->data = to_add;
    new_node->next = hash_table[index];
    hash_table[index] = new_node;

    return 1; 
}

int table::load_from_file(const char filename[])
{
    ifstream file_in(filename);
    if (!file_in)
    {
        cout << "Could not open file." << endl;
        return 0;
    }

    stream temp;
    char comma;

    while (!file_in.eof())
    {
        file_in.get(temp.stream_id, 20, ',');
        file_in.get(comma);

        file_in.get(temp.name, 50, ',');
        file_in.get(comma);

        file_in.get(temp.game, 50, ',');
        file_in.get(comma);

        file_in >> temp.viewers;
        file_in.get(comma);

        file_in >> temp.duration;
        file_in.get(comma);
        file_in.ignore(100, ',');

        file_in.get(temp.language, 30, ',');
        file_in.get(comma);

        file_in.get(temp.region, 30, ',');
        file_in.get(comma);

        file_in.get(temp.category, 50, ',');
        file_in.get(comma);

        file_in.get(temp.start_time, 30, '\n');
        file_in.ignore(100, '\n');

        if (!file_in.eof())
            insert(temp);
    }

    file_in.close();
    cout << "\nFile loaded successfully!\n";
    return 1;
}

int table::display_by_name(const char name[])
{
    int index = hash_function(name);
    node * current = hash_table[index];
    int found = 0;

    while (current)
    {
        if (strcasecmp(current->data.name, name) == 0)
        {
            cout << "\nStreamer: " << current->data.name
                 << "\nStream ID: " << current->data.stream_id
                 << "\nGame: " << current->data.game
                 << "\nViewers: " << current->data.viewers
                 << "\nDuration: " << current->data.duration
                 << "\nLanguage: " << current->data.language
                 << "\nRegion: " << current->data.region
                 << "\nCategory: " << current->data.category
                 << "\nStart Time: " << current->data.start_time
                 << "\n--------------------------------------\n";
            found++;
        }
        current = current->next;
    }

    if (!found)
        cout << "\nNo streams found for this name.\n";

    return found;
}

int table::retrieve(const char* name, stream*& matches, int& count, int max)
{
    int index = hash_function(name);
    node* current = hash_table[index];
    count = 0;

    
    matches = new stream[max];

    while (current && count < max)
    {
        if (strcasecmp(current->data.name, name) == 0)
        {
           
            matches[count].viewers = current->data.viewers;
            matches[count].duration = current->data.duration;

            matches[count].stream_id = new char[strlen(current->data.stream_id) + 1];
            strcpy(matches[count].stream_id, current->data.stream_id);

            matches[count].name = new char[strlen(current->data.name) + 1];
            strcpy(matches[count].name, current->data.name);

            matches[count].game = new char[strlen(current->data.game) + 1];
            strcpy(matches[count].game, current->data.game);

            matches[count].language = new char[strlen(current->data.language) + 1];
            strcpy(matches[count].language, current->data.language);

            matches[count].region = new char[strlen(current->data.region) + 1];
            strcpy(matches[count].region, current->data.region);

            matches[count].category = new char[strlen(current->data.category) + 1];
            strcpy(matches[count].category, current->data.category);

            matches[count].start_time = new char[strlen(current->data.start_time) + 1];
            strcpy(matches[count].start_time, current->data.start_time);

            count++;
        }
        current = current->next;
    }

    if (count == 0)
    {
        delete[] matches; 
        matches = nullptr;
        return 0;
    }

    return 1;
}

int table::display_all()
{
	return display_all_recursive(0, nullptr);
}


int table::display_all_recursive(int index, node* current)
{
    int total = 0;

    if (index >= table_size)
        return 0;

    
    if (!current)
        current = hash_table[index];

    if (current)
    {
        cout << "[" << index << "] " << current->data.name
             << " - " << current->data.game << endl;
        total = 1 + display_all_recursive(index, current->next);
    }
    else
    {
        total = display_all_recursive(index + 1, nullptr);
    }

    if (index == 0 && total == 0)
        cout << "No data to display.\n";
  return total;
}

int table::remove_by_name(const char name[])
{
    int index = hash_function(name);
    node * current = hash_table[index];
    node * previous = nullptr;
    int removed = 0;

    while (current)
    {
        if (compare_nocase(current->data.name, name) == 0)
        {
            node * to_delete = current;
            if (!previous)
                hash_table[index] = current->next;
            else
                previous->next = current->next;

            current = current->next;
	    delete[] to_delete->data.stream_id;
            delete[] to_delete->data.name;
            delete[] to_delete->data.game;
            delete[] to_delete->data.language;
            delete[] to_delete->data.region;
            delete[] to_delete->data.category;
            delete[] to_delete->data.start_time;

            delete to_delete;
            ++removed;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    if (!removed)
        return 0; 

    return 1; 
}

int table::display_by_game(const char game[])
{
    int found = 0;

    for (int i = 0; i < table_size; ++i)
    {
        node * current = hash_table[i];
        while (current)
        {
            if (compare_nocase(current->data.game, game) == 0)
            {
                cout << "\nStreamer: " << current->data.name
                     << "\nStream ID: " << current->data.stream_id
                     << "\nGame: " << current->data.game
                     << "\nViewers: " << current->data.viewers
                     << "\nDuration: " << current->data.duration
                     << "\nLanguage: " << current->data.language
                     << "\nRegion: " << current->data.region
                     << "\nCategory: " << current->data.category
                     << "\nStart Time: " << current->data.start_time
                     << "\n--------------------------\n";
                ++found;
            }
            current = current->next;
        }
    }

    if (!found)
        cout << "No streams found for this game.\n";

    return found; 
}

table::~table()
{
    for (int i = 0; i < table_size; ++i)
    {
        node* current = hash_table[i];
        while (current)
        {
            node* temp = current->next;

            
            delete[] current->data.stream_id;
            delete[] current->data.name;
            delete[] current->data.game;
            delete[] current->data.language;
            delete[] current->data.region;
            delete[] current->data.category;
            delete[] current->data.start_time;
            delete current;

            current = temp;
        }
        hash_table[i] = nullptr;
    }

    delete[] hash_table;
    hash_table = nullptr;
}

