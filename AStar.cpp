#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct anchor
{
    char label = '_';
    unsigned int h = 0;
    vector<char> parents;
    vector<char> childs;
    map<char, int> edge;
};

vector<anchor> create_anchors()
{
    vector<anchor> anchors;

    for (int i = 0;; i++)
    {
        anchor x;
        unsigned int num_of_child = 0, num_of_parent = 0;
        cout << "label: ";

        cin >> x.label;
        if (x.label == '$')
            break;
        x.label = toupper(x.label);

        cout << "h: ";
        cin >> x.h;

        x.edge.insert(std::pair<char, int>('A', 3));
        
        cout << "number of parent: ";
        cin >> num_of_parent;
        for (int j = 0; j < num_of_parent; j++)
        {
            char parent_label;
            cout << "parent label " << j + 1 << ": ";
            cin >> parent_label;
            x.parents.push_back(parent_label);
        }

        cout << "number of child: ";
        cin >> num_of_child;
        for (int j = 0; j < num_of_child; j++)
        {
            char child_label;
            cout << "child label " << j + 1 << ": ";
            cin >> child_label;
            x.childs.push_back(child_label);
        }

        anchors.push_back(x);
    }

    return anchors;
}

int get_min(vector<anchor> src)
{
    int min_idx = 0;
    int min_h = 9999999;
    for (size_t i = 0; i < src.size(); i++)
        if (src[i].h < min_h)
        {
            min_idx = i;
            min_h = src[i].h;
        }

    return min_idx;
}

anchor get_anchor_by_label(vector<anchor> anchors, char label)
{
    anchor x;
    for (size_t i = 0; i < anchors.size(); i++)
        if (toupper(label) == toupper(anchors[i].label))
            x = anchors[i];

    return x;
}

vector<char> combine_path(vector<char> src_path, anchor x) 
{
    for (size_t i = 0; i < src_path.size(); i++)
        for (size_t j = 0; j < x.parents.size(); j++)
            if (toupper(src_path[i]) == toupper(x.parents[j]))
            {
                src_path.resize(i + 1);
                break;
            }

    src_path.push_back(x.label);
    return src_path;
}

vector<char> befs(vector<anchor> anchors, char goal)
{
    vector<anchor> open, close;
    vector<char> path;
    open.push_back(anchors[0]);

    while (open.size() != 0)
    {
        int min_h_idx = get_min(open);
        anchor min_anchor = open[min_h_idx];

        path = combine_path(path, min_anchor);

        if (min_anchor.label == goal)
            break;

        for (size_t i = 0; i < min_anchor.childs.size(); i++) 
        {
            bool isExist = false;
            for (size_t j = 0; j < open.size(); j++)
                if (toupper(open[j].label) == toupper(min_anchor.childs[i]))
                    isExist = true;

            if (!isExist) 
                open.push_back(get_anchor_by_label(anchors, min_anchor.childs[i]));
        }
        
        close.push_back(min_anchor);
        open.erase(open.begin() + min_h_idx);

        cout << endl;
        for (size_t i = 0; i < path.size(); i++)
        {
            cout << path[i] << " ";
        }
    }

    return path;
}

int main()
{
    vector<anchor> anchors = create_anchors();
    vector<char> befs_path = befs(anchors, 'B');
    vector<int> chars;

    cout << endl;
    for (int i = 0; i < befs_path.size(); i++)
        cout << befs_path[i] << " ";

    return 0;
}

// a 14 0 4 c d e f / c 15 1 a 1 h / d 6 1 a 2 h e / e 8 1 a 2 k i / f 7 1 a 2 i g / h 10 2 c d 1 k / k 2 3 h e i 1 b / i 4 2 e f 1 b / g 12 1 f 0 / b 0 2 k i 0
// a 14 0 4 c d e f c 15 1 a 1 h d 6 1 a 2 h e e 8 1 a 2 k i f 7 1 a 2 i g h 10 2 c d 1 k k 2 3 h e i 1 b i 4 2 e f 1 b g 12 1 f 0 b 0 2 k i 0 $