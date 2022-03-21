#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<cctype>
#include<iomanip>
#include<fstream>
#include<cmath>
#define endl "\n"
using namespace std;
const string filename = "Students.dat";
struct Disc //структура, съдържааща име наа дисциплина и оценката по нея
{
    string disname;
    double grade;
};
struct student //основна структура - студент. съдържа всички характеристики за студента
{
    string faknum; //фак.номер
    string name; //име
    Disc disciplini[6];//дисциплини с имена и оценки
    string gender;
    short age;
    string status;
};
fstream fp; //файлов поток
void saveinfile(student sheet[], int n) //функция за запазване на структурата във файл. не е използвана по-нататък в програмата, понеже има проблеми с файловата обработка, които не успях да диагностицирам
{
    fp.open(filename, ios::binary | ios::out); //отваря се двоичен файл, декларира се, че ще се "пише" във файла
    if (!fp) { cout << "\n Error in file \n"; exit(1); } //съобщение за грешка, ако не се отвори правилно
    fp.write((char*)sheet, sizeof(student)*n); //стандартен начин за записване на масив от структури
    fp.close();
}
// n е броят на елементите в масива
int loadfile(student sheet[]) //функция за прочитане на информацията от двоичен файл
{
    long pos; int n = 0, i; student b;
    fp.open(filename, ios::binary | ios::in);
    if (!fp) { cout << "\n file not exist\n"; return n; }

    fp.seekg(0l, ios::end);
    pos = fp.tellg(); //променливата ни дава "стойността" на края на файла -
    fp.close();
    n = pos / (sizeof(student)); //използваме я за да разберем от колко елементи се състои масивът във файла
    fp.open(filename, ios::binary | ios::in);
    if (!fp) { cout << "\n Error in file \n"; exit(1); }
    for (i = 0; i < n; i++)
    {
        fp.read((char*)&b, sizeof(student)); //четем структурите една по една, записваме ги в b, а b записваме в sheet - основният ни масаив.
        sheet[i] = b;
    }
    fp.close();
    return n; //връщаме броят на елементите в масива
}
int addstud(short br, student ss[], int broika) //добавяне на елементи в масива
// подават се колко студенти ще бъдат добавени, основният масив и общият брой на елементите в него
{
    short i;
    for (i = broika; i < br + broika; i++) //цикълът за въвеждане започва от броя на елементите до същият+колко иска потребителят да добави
        // за да се записва всичко в правилна клетка на масиваа
    {
        fflush(stdin);
        if (i > 29) {
            cout << "Maksimalniqt broi studenti v grupata e zapulnen. Prekusvane na vuvejdaneto...\n"; //прекъсване, ако се надвиши лимита на групата
            break;
        }
        cout << "Zapochva dobavqne na student №"<<i+1<<"...\n";
        cout << "Vuvedi fak. nomer: "; cin >> ss[i].faknum;
        cout << "Vuvedi ime: "; fflush(stdin); cin.ignore(); getline(cin, ss[i].name);
        for (int j = 0; j < 5; j++)
        {
            cout << "Vuvedi imeto na disciplina nomer " << j+1 << ": ";
            fflush(stdin);  getline(cin, ss[i].disciplini[j].disname);
        }
        cout << "Vuvedi pol: "; cin >> ss[i].gender;
        cout << "Vuvedi vuzrast: "; cin >> ss[i].age;
        cout << "Vuvedi status: "; cin >> ss[i].status;
        cout << "OK...\n";

    }
    return i;
}
void izvediedin(student ss[], int i) //извежда конкретен студент, като се подава позицията му в масива
{
    cout << ss[i].faknum << " " << ss[i].name << "\nPol: " << ss[i].gender << "\nVuzrast: " << ss[i].age << "\nStatus: " << ss[i].status << endl;
    for (int j = 0; j < 5; j++)
    {
        cout << "Ocenka po " << ss[i].disciplini[j].disname << ": ";
        if (ss[i].disciplini[j].grade >= 2 && ss[i].disciplini[j].grade <= 6) cout << ss[i].disciplini[j].grade << endl; //Ако променливата на оценката не е от 2 до 6 или няма въведена оценка, или е въведена неправилно
        else cout << "Nqma\n";

    }
    cout << endl;

}
void izvedi(student ss[], int broika) //функцията извежда всички студенти от групата, подава се масивът и броят на елементите в него
{
    for (int i = 0; i < broika; i++)
    {
        cout << ss[i].faknum << " " << ss[i].name << "\nPol: " << ss[i].gender << "\nVuzrast: " << ss[i].age << "\nStatus: " << ss[i].status << endl;
        for (int j = 0; j < 5; j++)
        {
            cout << "Ocenka po " << ss[i].disciplini[j].disname << ": ";
            if (ss[i].disciplini[j].grade >= 2 && ss[i].disciplini[j].grade <= 6) cout << ss[i].disciplini[j].grade << endl; //Ако променливата на оценката не е от 2 до 6 или няма въведена оценка, или е въведена неправилно
            else cout << "Nqma\n";

        }
        cout << endl;
    }
}
void izvedibp(student ss[], int broika) //Открива учениците с най-ниска оценка по БП и ги извежда на екрана
{
    double minbp = 6;
    for (int i = 0; i < broika; i++) //цикълът открива минималната оценка по БП, като обхожда всички студенти и търси БП в дисциплините
    {
        for (int j = 0; j < 5; j++) {
            if (ss[i].disciplini[j].disname == "BP") {
                if (ss[i].disciplini[j].grade < minbp && ss[i].disciplini[j].grade >= 2) {
                    minbp = ss[i].disciplini[j].grade;
                }
                break; //прекъсва единствено разглеждането на оценки за студента, понеже дисциплина БП е открита
            }
        }
    }
    for (int i = 0; i < broika; i++) // ако се наамери ученик, който е с минимална оценка по БП, то той се извежда
    {
        for (int j = 0; j < 5; j++)
        {
            if (ss[i].disciplini[j].disname == "BP")
            {
                if (ss[i].disciplini[j].grade == minbp)izvediedin(ss, i);
                break;
            }
        }
    }
    
}
void addgrade(student ss[], string nomer, int broika) //функцията добавя оценки на студент, параметрите са основният масив; стринг факултетен номер и броят на елементите в масива
{
    bool prisustvie = 0; //променлива, показваща дали има студент с въведеен фак. номер в маасива.
    for (int i = 0; i < broika; i++)
    {
        if (nomer == ss[i].faknum) //проверка
        {
            prisustvie = 1;
            bool keke = 0; //показва дали има невъведени оценки на студент
            for (int j = 0; j < 5; j++)
            {
                if (ss[i].disciplini[j].grade < 2 || ss[i].disciplini[j].grade > 6)
                {

                    short ppp;
                    cout << "Nqma vuvedena ocenka po " << ss[i].disciplini[j].disname << ". Za da se dobavi ocenka po " << ss[i].disciplini[j].disname << " vuvedete ""1"". V protiven sluchai vuvedete neshto drugo.\n";
                    cin >> ppp;
                    if (ppp == 1)
                    {
                        cout << "Vuvedete ocenkata: ";
                        cin >> ss[i].disciplini[j].grade;
                        if (ss[i].disciplini[j].grade >= 2 && ss[i].disciplini[j].grade <= 6) cout << "Ocenkata e uspeshno vuvedena.\n";
                        else cout << "Nevalidna ocenka. Ocenkata ne e vuvedena.\n";

                    }
                }

            }
            for (int j = 0; j < 5; j++)
            {
                if ((ss[i].disciplini[j].grade < 2 || ss[i].disciplini[j].grade>6))
                {
                    keke = 1; //има невъведена оценка
                    break;
                }
            }
            if (keke == 0)cout << "Vsichki ocenki na studenta sa vuvedeni.\n";
        }
    }
    if (prisustvie == 0)cout << "Student s takuv fakulteten nomer ne prisustva.\n";
}
void graduator(student ss[], string d, int broika) //проста функция, променяща статусът на ученик спрямо името му.
{
    for (int i = 0; i < broika; i++)
    {
        if (d == ss[i].name)
        {
            ss[i].status = "zavurshil";
            cout << "Statusut na " << ss[i].name << " e promenen na \"" << ss[i].status << "\".\n";
            break;
        }
    }
}
void ocenkinator(student ss[], string d, int broika)//функция, променяща оценките на студент, параметърът d е факултетен номер
{
    for (int i = 0; i < broika; i++)
    {
        if (ss[i].faknum == d) //otkrivaa se studentut
        {
            for (int j = 0; j < 5; j++)
            {
                cout << "Za da promenite ocenkata po " << ss[i].disciplini[j].disname << " vuvedete ""1"". V protiven sluchai, vuvedete drugo.\n";
                short sos; cin >> sos;
                if (sos == 1)
                {
                    cout << "Vuvedete novata ocenka po " << ss[i].disciplini[j].disname << ": ";
                    double ococ; cin >> ococ;
                    if (ococ > 6 || ococ < 2)cout << "Nevalidna ocenka! Ostavena e predishnata stoinost...\n";
                    else {
                        ss[i].disciplini[j].grade = ococ;
                        cout << "Novata ocenka po " << ss[i].disciplini[j].disname << " e: " << ss[i].disciplini[j].grade << ".\n";
                    }
                }
            }
            break;
        }
    }
}
string podgotvitel(string purvi) //функцията се използва при сортирането на студенти по азбучен ред
// подава ѝ се стринг, който е име на студент и се връща същия, само че с малки букви и без интервали. направих функцията, защото при сравняваане по ascii код
// главните букви винаги са "по-малки" от малките, а това създава обърквания при по-сложни имена, които съдържат "van","дьо" и подобни...
{
    purvi.erase(remove_if(purvi.begin(), purvi.end(), isspace), purvi.end()); //премахват се интервалите 
    transform(purvi.begin(), purvi.end(), purvi.begin(), ::tolower);//всички букви се правят малки
    return purvi;
}
void sortabc(student ss[], int broika) //извежда всички студенти на екрана, сортирани по латински/английски азбучен ред
{
    vector<string> podred; //записвам обработените имена на студентите във вектор, за по-лесна обработка
    for (int i = 0; i < broika; i++)
    {
        string a = podgotvitel(ss[i].name);
        podred.push_back(a);
    }
    sort(podred.begin(), podred.end()); //сортирам всичките имена по азбучен ред
    for (int i = 0; i < broika; i++) //троен цикъл. не е най-бързият вариант, но работи
        //обхожда се всеки студент
    {
        for (int j = 0; j < broika; j++)
        {
            string a = podgotvitel(ss[j].name); //извеждат се студентите според реда им в сортирания вектор
            if (podred[i] == a)
            {
                cout << ss[j].faknum << " " << ss[j].name << "\nPol: " << ss[j].gender << "\nVuzrast: " << ss[j].age << "\nStatus: " << ss[j].status << endl;
                for (int k = 0; k < 5; k++)
                {
                    cout << "Ocenka po " << ss[j].disciplini[k].disname << ": ";
                    if (ss[j].disciplini[k].grade >= 2 && ss[j].disciplini[k].grade <= 6) cout << ss[j].disciplini[k].grade << endl;
                    else cout << "Nqma\n";

                }
                cout << endl; break;
            }
        }
    }


}
void sortage(student ss[], int broika) //извеждат се всички студенти, сортирани по възраст.
//алгоритъмът е същият като сортирането по азбучен ред
{
    vector<short> ages;
    for (int i = 0; i < broika; i++)
        ages.push_back(ss[i].age);
    sort(ages.begin(), ages.end());
    for (int i = 0; i < broika; i++)
        for (int j = 0; j < broika; j++)
            if (ages[i] == ss[j].age)
            {
                cout << ss[j].faknum << " " << ss[j].name << "\nPol: " << ss[j].gender << "\nVuzrast: " << ss[j].age << "\nStatus: " << ss[j].status << endl;
                for (int k = 0; k < 5; k++)
                {
                    cout << "Ocenka po " << ss[j].disciplini[k].disname << ": ";
                    if (ss[j].disciplini[k].grade >= 2 && ss[j].disciplini[k].grade <= 6) cout << ss[j].disciplini[k].grade << endl;
                    else cout << "Nqma\n";

                }
                cout << endl; break;
            }
}
void polovete(student ss[], int broika)// извежда най-м
{
    vector<short> fages, mages;
    for (int i = 0; i < broika; i++) //векторите се запълват с възрастите на жените и възрастите на мъжете
    {
        if (ss[i].gender == "male")mages.push_back(ss[i].age);
        if (ss[i].gender == "female")fages.push_back(ss[i].age);
    }
    sort(fages.begin(), fages.end()); sort(mages.begin(), mages.end());//сортира се, за да се открие най-ниската възраст
    for (int j = 0; j < broika; j++) //обхожда се всеки студент и се извеждааат най-младите по възраст от пола
    {
        if (ss[j].gender == "male" && ss[j].age == mages[0]) 
        {

            
            cout << ss[j].faknum << " " << ss[j].name << "\nPol: " << ss[j].gender << "\nVuzrast: " << ss[j].age << "\nStatus: " << ss[j].status << endl;
            for (int k = 0; k < 5; k++)
            {
                cout << "Ocenka po " << ss[j].disciplini[k].disname << ": ";
                if (ss[j].disciplini[k].grade >= 2 && ss[j].disciplini[k].grade <= 6) cout << ss[j].disciplini[k].grade << endl;
                else cout << "Nqma\n";

            }
            cout << endl;
        }
        if (ss[j].gender == "female" && ss[j].age == fages[0])
        {

            
            cout << ss[j].faknum << " " << ss[j].name << "\nPol: " << ss[j].gender << "\nVuzrast: " << ss[j].age << "\nStatus: " << ss[j].status << endl;
            for (int k = 0; k < 5; k++)
            {
                cout << "Ocenka po " << ss[j].disciplini[k].disname << ": ";
                if (ss[j].disciplini[k].grade >= 2 && ss[j].disciplini[k].grade <= 6) cout << ss[j].disciplini[k].grade << endl;
                else cout << "Nqma\n";

            }
            cout << endl;
        }
    }
}
void avgusp(student ss[], int broika) //открива се студента с най-високият среден успех и се извежда на екрана
{
    double highest = 2; int maxi=0;
    for (int i = 0; i < broika; i++) //открива се най-високият среден успех
    {
        double sr = 0; short broc = 0;
        for (int k = 0; k < 5; k++)
        {
            if (ss[i].disciplini[k].grade >= 2 && ss[i].disciplini[k].grade <= 6)
            {
                sr += ss[i].disciplini[k].grade; //открива се средният успех част 1
                broc++;
            }
        }
        if (broc>0)sr /= broc; //октирва се средният успех част 2
        if (sr > highest) { //ако се открие по-висок от досегашния най-висок среден успех, запазваме позицията на студента и назначаваме нов макс. среден успех.
            maxi = i; highest = sr;
        }
        cout << "Sredniqt uspeh na " << ss[i].name << " e: " << sr << endl;//извежда се средният успех на всеки студент за улеснение и 
        //проверка за коректност на програмата, може редът да се закоментари
    }
    //извеждаме студентът с най-висок среден успех
    cout << ss[maxi].faknum << " " << ss[maxi].name << "\nPol: " << ss[maxi].gender << "\nVuzrast: " << ss[maxi].age << "\nStatus: " << ss[maxi].status << endl;
    for (int k = 0; k < 5; k++)
    {
        cout << "Ocenka po " << ss[maxi].disciplini[k].disname << ": ";
        if (ss[maxi].disciplini[k].grade >= 2 && ss[maxi].disciplini[k].grade <= 6) cout << ss[maxi].disciplini[k].grade << endl;
        else cout << "Nqma\n";

    }
    cout << endl;

}
int main() //мейн, съдържаащ менюто
{
    cout << "Za mujki i jenski pol molq izpolzvaite \"male\" i \"female\"!\n"; //пояснение
    cout << endl;
    student sheet[32]; //основния масив от структури
    int alle = 0;//loadfile(sheet);
    short a; //променлива за работаа с менюто
    do {

        cout << "\nZdraveite, za da dobavite student/i v grupata vuvedete ""1"". \nZa da izvedete studenti na ekrana vuvedete ""2"".\nZa da vuvedete ocenki na student vuvedete ""3"".\nZa da promenite studentite v grupata, vuvedete ""4"".\n";
        cout << "Za da napravite spravki za studentite, vuvedete ""5"".\nZa da zapishete dannite v dvoichen fail, vuvedete 6.\nZa da izlezete ot programata, vuvedete 7.\n";
        cin >> a;
        if (a == 1)
        {
            cout << "Ako iskate da dobavite edin student v grupata vuvedete ""1"".\nZa da dobavite poveche, vuvedete ""2""\n";
            short k; cin >> k;
            if (k == 1)
            {
                alle = addstud(1, sheet, alle); /*saveinfile(sheet, alle);*/
                short cirk;
                do
                {
                    cout << "Za da dobavite oshte edin student, vuvedete 1; v protiven sluchai, vuvedete neshto drugo.";
                    cin >> cirk;
                    if (cirk == 1) { alle = addstud(1, sheet, alle); /*saveinfile(sheet, alle);*/ }
                } while (cirk == 1);
            }
            else {
                short s;
                cout << "Vuvedete broqt na studenti, koito iskate da dobavite: "; cin >> s;
                alle = addstud(s, sheet, alle); saveinfile(sheet, alle);
            }
        }
        if (a == 2)
        {
            cout << "Za da izvedete vsichki studenti na ekrana, vuvedete ""1"".\nZa da izvedete studenti s minimalna ocenka po BP, vuvedete ""2"".\n";
            short k; cin >> k;
            if (k == 1)izvedi(sheet, alle);
            if (k == 2)izvedibp(sheet, alle);
        }
        if (a == 3)
        {
            string fakfak;
            cout << "Vuvedete fakulteten nomer na studenta: ";
            cin >> fakfak;
            addgrade(sheet, fakfak, alle);
            /*saveinfile(sheet, alle);*/
        }
        if (a == 4)
        {
            cout << "Za da promenite statusa na student na zavurshil, vuvedete ""1"".\nZa da promenite ocenkite na student, vuvedete ""2"".\n";
            short k; cin >> k;
            if (k == 1)
            {
                string umora; cout << "Vuvedete imeto na studenta: "; getline(cin, umora); getline(cin, umora);
                graduator(sheet, umora, alle);
                /*saveinfile(sheet, alle);*/
            }
            if (k == 2)
            {
                string fakulnum; cout << "Vuvedete fakultetniq nomer na studenta: "; cin >> fakulnum;
                ocenkinator(sheet, fakulnum, alle);
                /*saveinfile(sheet, alle);*/
            }


        }
        if (a == 5)
        {
            cout << "Za da izvedete studentite v podreden red, vuvedete ""1"".\nZa da izvedete nai-mladite studenti po pol, vuvedete ""2"".\nZa da izvedete studenta s nai-visok sreden uspeh, vuvedete ""3"".\n";
            short k; cin >> k;
            if (k == 1)
            {
                cout << "Vuvedete \"1\" za azbuchen red(latinska azbuka) ili \"2\" za vuzhodqshta vuzrast.";
                short skt; cin >> skt;
                if (skt == 1)sortabc(sheet, alle);
                if (skt == 2)sortage(sheet, alle);

            }
            if (k == 2)
            {
                polovete(sheet, alle);
            }
            if (k == 3)
            {
                avgusp(sheet, alle);
            }
        }
        if (a == 6) {
            cout << "Ne e sigurno dali raboti kato horata, no masivut e zapisan...\n";
            saveinfile(sheet, alle);

        }


    } while (a != 7);
    return 0;
}
