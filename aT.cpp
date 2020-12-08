#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct anchor
{
    char label = '_';
    unsigned int g = 0;
    vector<char> parents;
    vector<char> childs;
    map<char, int> cost;
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
            int cost;
            cout << "child label " << j + 1 << ": ";
            cin >> child_label;
            cout << "cost(" << x.label << ", " << child_label << "): ";
            cin >> cost;
            x.childs.push_back(child_label);
            x.cost.insert(std::pair<char, int>(child_label, cost));
        }

        anchors.push_back(x);
    }

    return anchors;
}

int get_min(vector<anchor> src)
{
    int min_id = 0;
    int min_g = 9999999;
    for (size_t i = 0; i < src.size(); i++)
        if (src[i].g < min_g)
        {
            min_id = i;
            min_g = src[i].g;
        }

    return min_id;
}

int get_anchor_id_by_label(vector<anchor> anchors, char label)
{
    for (size_t i = 0; i < anchors.size(); i++)
        if (toupper(label) == toupper(anchors[i].label))
            return i;
    return -1;
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

vector<char> aT(vector<anchor> anchors, char goal)
{
    vector<anchor> open, close;
    vector<char> path; // mảng lưu đường đi
    open.push_back(anchors[0]);

    while (open.size() != 0)
    {
        int min_g_id = get_min(open); // lay index thang co F nho nhat trong open
        anchor min_anchor = open[min_g_id];

        path = combine_path(path, min_anchor);

        if (min_anchor.label == goal)
            break;

        // duyệt qua các đỉnh con của đỉnh đang xét
        for (size_t i = 0; i < min_anchor.childs.size(); i++)
        {
            bool isExist = false; // vòng for để kiểm tra cái đỉnh nhỏ nhất có trong OPEN chưa, nếu có rồi thì không thêm vào OPEN
            char child_label = min_anchor.childs[i];
            for (size_t j = 0; j < open.size(); j++)
                if (toupper(open[j].label) == toupper(child_label))
                    isExist = true;

            // Thêm vào OPEN
            if (!isExist)
            {
                int child_id = get_anchor_id_by_label(anchors, child_label); // lấy index đỉnh con của đỉnh đang xét
                anchor child_anchor = anchors[child_id];
                int g = min_anchor.g + min_anchor.cost[child_label]; // cộng dồn theo thuật toán

                // gán g sau khi cộng dồn vào đỉnh con
                // từ đó sẽ tận dụng được ở các vòng lặp sau, cụ thể là ở dòng 96, hàm get_min()
                child_anchor.g = g;

                open.push_back(child_anchor);
            }
        }

        // thêm đỉnh đang xét vào CLOSE, xóa khỏi OPEN
        close.push_back(min_anchor);
        open.erase(open.begin() + min_g_id);

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
    vector<char> path = aT(anchors, 'H');
    vector<int> chars;

    cout << endl;
    for (int i = 0; i < path.size(); i++)
        cout << path[i] << " ";

    return 0;
}

// a 0 3 b 2 c 4 f 6 / b 1 a 0 / c 1 a 2 d 8 f 2 / f 1 a 2 g 5 h 1 / d 1 c 0 / e 1 c 0 / g 1 f 0 / h 1 f 0
// a 0 3 b 2 c 4 f 6 b 1 a 0 c 1 a 2 d 8 f 2 f 1 a 2 g 5 h 1 d 1 c 0 e 1 c 0 g 1 f 0 h 1 f 0
