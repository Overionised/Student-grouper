using namespace std;

string shuffler(){
    srand((unsigned)time(0));
    string missing,exit;
    int r1,r2,ct=0;
    string trida[2][15] = {
            {"Vojtech Bien", "David Boucek", "Jakub Dopan", "Josef Hasek", "Artur Havrylenko", "Jan Herza", "Milan Holecek", "Mikulas Chlup", "Ondrej Kacer", "Vojtech Kminek", "Nori Koci", "Veronika Kominkova", "Amelie Martini", "Stepan Skruzny", "Miroslav Klasna"},
            {"Bien", "Boucek", "Dopan", "Hasek", "Havrylenko", "Herza", "Holecek", "Chlup", "Kacer", "Kminek", "Koci", "Kominkova", "Martini", "Skruzny", "Klasna"}
                };
    //chybi nekdo input
    do{
        cout<<"chybi nekdo?: ";
        cin>>missing;
        system("CLS");

        for(int i=0;i<sizeof(trida)[1]/sizeof(string);i++){
            if(missing==trida[1][i]){
                trida[0][i]="*";
                cout<<"zapsano"<<endl;
                break;
                }
        }
    }
    while(missing!="0");

    //proswapuje array
    for(int i=0;i<sizeof(trida)[1]/sizeof(string);i++){
        r1 = (rand() % sizeof(trida[1])/sizeof(string));
        r2 = (rand() % sizeof(trida[1])/sizeof(string));
        swap(trida[0][r1],trida[0][r2]);
    }
    //vypise
    for(int i=0;i<sizeof(trida)[1]/sizeof(string);i++){
        if(trida[0][i]!="*"){
            cout<<trida[0][i];
            ct++;
                if(ct==1){
                    cout<<" - ";
        }

        }if(ct==2){
            cout<<endl<<endl;
            ct=0;
        }
    }
    //manual exit
    cout<<endl<<endl<<"type anything to exit: ";
    cin>>exit;
}
