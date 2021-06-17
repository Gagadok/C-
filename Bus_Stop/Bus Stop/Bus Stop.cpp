#include "WorkingWithFiles.h"
#include "DataProcessing.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    string input_path = "In.txt";
    string output_path = "Out.txt";
    queue <string> data;
    WorkingWithFiles wwf = WorkingWithFiles();
    cout << "Enter input file: ";
    getline(cin, input_path);
    if (wwf.Loading(input_path))
    {
        cout << "Enter output file: ";
        getline(cin, output_path);
        data = wwf.GetData();
        DataProcessing dp = DataProcessing(data);
        data = dp.MakeSchedule();
        wwf.Write(output_path, data);
    }
    system("pause");
}