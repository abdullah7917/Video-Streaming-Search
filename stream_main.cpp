//Abdullah Ali Khan, CS163- in person,11/14/2025
//This takes input from user and call the fuctions 

#include "stream.h"

void input_stream(stream & s)
{
    cout << "\nEnter Stream ID: ";
    cin.get(s.stream_id, 20);
    cin.ignore(100, '\n');

    cout << "Enter Streamer Name (key): ";
    cin.get(s.name, 50);
    cin.ignore(100, '\n');

    cout << "Enter Game: ";
    cin.get(s.game, 50);
    cin.ignore(100, '\n');

    cout << "Enter Viewers: ";
    cin >> s.viewers;
    cin.ignore(100, '\n');

    cout << "Enter Duration (minutes): ";
    cin >> s.duration;
    cin.ignore(100, '\n');

    cout << "Enter Language: ";
    cin.get(s.language, 30);
    cin.ignore(100, '\n');

    cout << "Enter Region: ";
    cin.get(s.region, 30);
    cin.ignore(100, '\n');

    cout << "Enter Category: ";
    cin.get(s.category, 50);
    cin.ignore(100, '\n');

    cout << "Enter Start Time: ";
    cin.get(s.start_time, 30);
    cin.ignore(100, '\n');
}

int main()
{
    table my_table(SIZE);
    table my_table2(97);
    int collisions1 = 0;
    int collisions2 = 0;

    int num_streams;
    cout << "Enter number of streams: ";
    cin >> num_streams;
    cin.ignore(100, '\n');
stream* streams = new stream[num_streams];
   for (int i = 0; i < num_streams; ++i)
    {
        input_stream(streams[i]); 
    }
    for (int i = 0; i < num_streams; ++i)
    {     
        my_table.insert_with_collision_count(streams[i], collisions1, false);
    }

    
    for (int i = 0; i < num_streams; ++i)
    {
        my_table2.insert_with_collision_count(streams[i], collisions2, true);
    }

    cout << "Collisions with first hash (table 101): " << collisions1 << endl;
    cout << "Collisions with second hash (table 97): " << collisions2 << endl;
    
    delete[] streams;
    
    int choice;

    do {
        cout << "\n MENU \n";
	cout << "1. Load from file\n";
        cout << "2. Insert new stream\n";
        cout << "3. Display all streams\n";
        cout << "4. Search by streamer name\n";
        cout << "5. Retrieve by name\n";
	cout << "6. Remove by streamer name\n";
	cout << "7. Remove by streamer name\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(100, '\n');
	
	if (choice == 1)
	{
		my_table.load_from_file("video_game_streaming.txt");
	}

	else if (choice == 2)
        {
            stream temp;
            input_stream(temp); 
            my_table.insert(temp);
            cout << "\nStream inserted successfully!\n";
        }
        else if (choice == 3)
        {
            int total = my_table.display_all();
            cout << "Total entries: " << total << endl;
        }
        else if (choice == 4)
        {
            char name[50];
            cout << "Enter streamer name: ";
            cin.get(name, 50);
            cin.ignore(100, '\n');
            my_table.display_by_name(name);
        }
        else if (choice == 5)
        {
            char name[50];
            cout << "Enter streamer name: ";
            cin.get(name, 50);
            cin.ignore(100, '\n');

            stream * result = nullptr;
            int count = 0;

            if (my_table.retrieve(name, result, count, 50))
            {
                cout << "\nRetrieved " << count << " stream(s):\n";
                for (int i = 0; i < count; ++i)
                {
                    cout << result[i].name << " - "
                         << result[i].game << endl;
                }
            }
	
            else
            {
                cout << "No streams found for " << name << endl;
            }
	}

	else if (choice == 6)
        {
            char name[50];
            cout << "Enter streamer name to remove: ";
            cin.get(name, 50);
            cin.ignore(100, '\n');

            if (my_table.remove_by_name(name))
                cout << "All streams for " << name << " removed.\n";
            else
                cout << "No streams found for " << name << endl;
        }

	else if (choice == 7)
        {
            char game[50];
            cout << "Enter game name: ";
            cin.get(game, 50);
            cin.ignore(100, '\n');

            int count = my_table.display_by_game(game);
            cout << "Total streams found for this game: " << count << endl;
        }
	
    } while (choice != 8);

    cout << "\nThank you.\n";
    return 0;
}

