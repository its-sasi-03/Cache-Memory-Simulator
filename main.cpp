#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void directMapping()
{
    int cacheSize;

    cout << "Enter Cache Size: ";
    cin >> cacheSize;

    vector<int> cache(cacheSize, -1);

    int n;

    cout << "Enter Number of Memory Accesses: ";
    cin >> n;

    int hits = 0;
    int misses = 0;

    cout << "Enter Memory Access Sequence:\n";

    for(int i = 0; i < n; i++)
    {
        int block;
        cin >> block;

        int line = block % cacheSize;

        if(cache[line] == block)
        {
            hits++;
            cout << block << " -> HIT\n";
        }
        else
        {
            misses++;
            cache[line] = block;

            cout << block << " -> MISS\n";
        }
    }

    cout << "\nFinal Cache:\n";

    for(int i = 0; i < cacheSize; i++)
    {
        cout << "Line "
             << i
             << " : ";

        if(cache[i] == -1)
            cout << "Empty";
        else
            cout << "Block " << cache[i];

        cout << endl;
    }

    cout << "\nHits: " << hits;
    cout << "\nMisses: " << misses;
    cout << "\nHit Ratio: "
         << (double)hits / (hits + misses)
         << endl;
}

void fullyAssociative()
{
    int cacheSize;

    cout << "Enter Cache Size: ";
    cin >> cacheSize;

    vector<int> cache;

    int n;

    cout << "Enter Number of Memory Accesses: ";
    cin >> n;

    int hits = 0;
    int misses = 0;

    int replacementIndex = 0;

    cout << "Enter Memory Access Sequence:\n";

    for(int i = 0; i < n; i++)
    {
        int block;
        cin >> block;

        auto it = find(cache.begin(),
                       cache.end(),
                       block);

        if(it != cache.end())
        {
            hits++;
            cout << block << " -> HIT\n";
        }
        else
        {
            misses++;

            if(cache.size() < cacheSize)
            {
                cache.push_back(block);
            }
            else
            {
                cache[replacementIndex] = block;

                replacementIndex =
                    (replacementIndex + 1)
                    % cacheSize;
            }

            cout << block << " -> MISS\n";
        }
    }

    cout << "\nFinal Cache:\n";

    for(int i = 0; i < cache.size(); i++)
    {
        cout << "Line "
             << i
             << " : Block "
             << cache[i]
             << endl;
    }

    cout << "\nHits: " << hits;
    cout << "\nMisses: " << misses;
    cout << "\nHit Ratio: "
         << (double)hits / (hits + misses)
         << endl;
}

void setAssociative()
{
    int cacheSize, setSize;

    cout << "Enter Cache Size: ";
    cin >> cacheSize;

    cout << "Enter Set Size: ";
    cin >> setSize;

    int numSets = cacheSize / setSize;

    vector<vector<int>> cache(numSets);

    int n;

    cout << "Enter Number of Memory Accesses: ";
    cin >> n;

    int hits = 0;
    int misses = 0;

    cout << "Enter Memory Access Sequence:\n";

    for(int i = 0; i < n; i++)
    {
        int block;
        cin >> block;

        int setIndex = block % numSets;

        auto &currentSet = cache[setIndex];

        auto it = find(currentSet.begin(),
                       currentSet.end(),
                       block);

        if(it != currentSet.end())
        {
            hits++;

            cout << block
                 << " -> HIT\n";
        }
        else
        {
            misses++;

            if(currentSet.size() < setSize)
            {
                currentSet.push_back(block);
            }
            else
            {
                currentSet.erase(currentSet.begin());

                currentSet.push_back(block);
            }

            cout << block
                 << " -> MISS\n";
        }
    }

    cout << "\nFinal Cache State:\n";

    for(int i = 0; i < numSets; i++)
    {
        cout << "Set "
             << i
             << " : ";

        for(int block : cache[i])
        {
            cout << block << " ";
        }

        cout << endl;
    }

    cout << "\nHits: "
         << hits;

    cout << "\nMisses: "
         << misses;

    cout << "\nHit Ratio: "
         << (double)hits /
            (hits + misses)
         << endl;
}
void fullyAssociativeLRU()
{
    int cacheSize;

    cout << "Enter Cache Size: ";
    cin >> cacheSize;

    vector<int> cache;

    int n;

    cout << "Enter Number of Memory Accesses: ";
    cin >> n;

    int hits = 0;
    int misses = 0;

    cout << "Enter Memory Access Sequence:\n";

    for(int i = 0; i < n; i++)
    {
        int block;
        cin >> block;

        auto it = find(cache.begin(),
                       cache.end(),
                       block);

        if(it != cache.end())
        {
            hits++;

            cache.erase(it);

            cache.push_back(block);

            cout << block
                 << " -> HIT\n";
        }
        else
        {
            misses++;

            if(cache.size() < cacheSize)
            {
                cache.push_back(block);
            }
            else
            {
                cache.erase(cache.begin());

                cache.push_back(block);
            }

            cout << block
                 << " -> MISS\n";
        }
    }

    cout << "\nFinal Cache:\n";

    for(int i = 0; i < cache.size(); i++)
    {
        cout << "Line "
             << i
             << " : Block "
             << cache[i]
             << endl;
    }

    cout << "\nHits: "
         << hits;

    cout << "\nMisses: "
         << misses;

    cout << "\nHit Ratio: "
         << (double)hits /
            (hits + misses)
         << endl;
}

int main()
{
    int choice;

    cout << "\n===== Cache Memory Simulator =====\n";

    cout << "1. Direct Mapping\n";
    cout << "2. Fully Associative\n";
    cout << "3. Set Associative\n";
    cout << "4. Fully Associative (LRU)\n";
    cout << "5. Exit\n";

    cout << "\nEnter Choice: ";
    cin >> choice;

    switch(choice)
    {
        case 1:
            directMapping();
            break;

        case 2:
            fullyAssociative();
            break;

        case 3:
            setAssociative();
            break;

        case 4:
            fullyAssociativeLRU();
            break;

        case 5:
            return 0;
            

        default:
            cout << "Invalid Choice\n";
    }

    return 0;
}