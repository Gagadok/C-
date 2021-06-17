#include "WorkingWithFiles.h"

queue<string> WorkingWithFiles::GetData()
{
    return data;
}

bool WorkingWithFiles::Loading(string path)
{
    ifstream file(path);
    if (file.is_open())
    {
        int n = 20;
        char* tmp = new char[n];
        while (!file.eof())
        {
            file.getline(tmp, n);
            data.push(tmp);
        }
        file.close();
        delete[] tmp;
        return true;
    }
    else
    {
        cout << "File opening problem \"" << path << "\"" << endl;
        file.close();
        return false;
    }
}

bool WorkingWithFiles::Write(string path, queue <string> data)
{
    ofstream out;
    out.open(path);
    if (out.is_open())
    {
        while (!data.empty())
        {
            out << data.front() << endl;
            data.pop();
        }
        out.close();
        cout << "Done. Open the file \"" << path << "\"" << endl;
        return true;
    }
    else
    {
        cout << "File opening problem \"" << path << "\"" << endl;
        out.close();
        return false;
    }
}