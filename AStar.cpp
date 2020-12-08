#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct anchor
{
    char label = '_';
    unsigned int h = 0;
    unsigned int g = 0;
    unsigned int f = 0;
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

        cout << "h: ";
        cin >> x.h;
        
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
    int min_idx = 0;
    int min_f = 9999999;
    for (size_t i = 0; i < src.size(); i++)
        if (src[i].f < min_f)
        {
            min_idx = i;
            min_f = src[i].f;
        }

    return min_idx;
}

int get_anchor_idx_by_label(vector<anchor> anchors, char label)
{
    for (size_t i = 0; i < anchors.size(); i++)
        if (toupper(label) == toupper(anchors[i].label))
            return i;
    return -1;
}

vector<char> a_star(vector<anchor> anchors, char goal)
{
    vector<anchor> open, close;
    vector<char> path; // mảng lưu đường đi
    open.push_back(anchors[0]);

    while (open.size() != 0)
    {
        int min_f_idx = get_min(open); // lay index thang co F nho nhat trong open
        anchor min_anchor = open[min_f_idx];

        path.push_back(min_anchor.label); // thêm vào đường đi

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
                int child_idx = get_anchor_idx_by_label(anchors, child_label); // lấy index đỉnh con của đỉnh đang xét
                anchor child_anchor = anchors[child_idx];
                int g = min_anchor.g + min_anchor.cost[child_label]; // cộng dồn theo thuật toán
                int f = g + anchors[child_idx].h; // cộng dồn theo thuật toán

                // gán lại F và G sau khi cộng dồn vào đỉnh con
                // từ đó sẽ tận dụng được ở các vòng lặp sau, cụ thể là ở dòng 96, hàm get_min()
                child_anchor.g = g; 
                child_anchor.f = f;

                open.push_back(child_anchor);
            }
        }
        
        // thêm đỉnh đang xét vào CLOSE, xóa khỏi OPEN
        close.push_back(min_anchor);
        open.erase(open.begin() + min_f_idx);

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
    vector<char> a_star_path = a_star(anchors, 'B');
    vector<int> chars;

    cout << endl;
    for (int i = 0; i < a_star_path.size(); i++)
        cout << a_star_path[i] << " ";

    return 0;
}

// a 14 0 4 c 9 d 7 e 13 f 20 / c 15 1 a 1 h 6 / d 6 1 a 2 h 8 e 4 / e 8 1 a 2 k 4 i 3 / f 7 1 a 2 i 6 g 4 / h 10 2 c d 1 k 5 / k 2 3 h e i 1 b 6 / i 4 2 e f 1 b 5 / g 12 1 f 0 / b 0 2 k i 0
// a 14 0 4 c 9 d 7 e 13 f 20 c 15 1 a 1 h 6 d 6 1 a 2 h 8 e 4 e 8 1 a 2 k 4 i 3 f 7 1 a 2 i 6 g 4 h 10 2 c d 1 k 5 k 2 3 h e i 1 b 6 i 4 2 e f 1 b 5 g 12 1 f 0 b 0 2 k i 0
// a 14 0 4 c 9 d 7 e 13 f 20 c 15 1 a 1 h 6 d 6 1 a 2 h 8 e 4 e 8 1 a 2 k 4 i 3 f 7 1 a 2 g 4 i 6 h 10 2 c d 1 k 5 k 2 3 h e i 1 b 6 i 4 2 e f 1 b 5 g 12 1 f 0 b 0 2 k i 0