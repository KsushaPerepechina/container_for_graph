#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
using namespace std;

int menu();

int menu() // Ìåíþ
{
    int i;
    cout << "Âûáåðèòå:" << endl;
    cout << "1. Ïðîâåðêà ïðèñóòñòâèÿ âåðøèíû â ãðàôå" << endl;
    cout << "2. Ïðîâåðêà ïðèñóòñòâèÿ ðåáðà ìåæäó âåðøèíàìè â ãðàôå" << endl;
    cout << "3. Ïîëó÷åíèå êîëè÷åñòâà âåðøèí" << endl;
    cout << "4. Ïîëó÷åíèå êîëè÷åñòâà ðåáåð" << endl;
    cout << "5. Âû÷èñëåíèå ñòåïåíè âåðøèíû" << endl;
    cout << "6. Âû÷èñëåíèå ñòåïåíè ðåáðà" << endl;
    cout << "7. Äîáàâëåíèå âåðøèíû" << endl;
    cout << "8. Äîáàâëåíèå ðåáðà" << endl;
    cout << "9. Óäàëåíèå âåðøèíû" << endl;
    cout << "10. Óäàëåíèå ðåáðà" << endl;
    cout << "11. Âûõîä" << endl;
    cin >> i;
    return i;
}

int main ()
{
    int k;
    bool est;
    int u,v;
    setlocale(LC_ALL,"Rus");
    int p=1;
    //çàäàíèå ãðàôà íà 20 âåðøèí
    Graph<int>  G(20);
    est=G.empty();
    if (est==true)
        cout<<"Âåðøèíû â ãðàôå îòñóòñòâóþò."<<endl;
    //äîáàâëåíèå âåðøèí
    G.add_vertex(0);
    G.add_vertex(1);
    G.add_vertex(2);
    G.add_vertex(3);
    G.add_vertex(4);
    G.add_vertex(5);
    G.add_vertex(6);
    G.add_vertex(7);

    //äîáàâëåíèå ðåáåð
    G.add_edge(0, 7);
    G.add_edge(0, 0);
    G.add_edge(1, 2);
    G.add_edge(2, 3);
    G.add_edge(4, 2);
    G.add_edge(3, 5);
    G.add_edge(3, 6);
    G.add_edge(5, 0);

    est=G.empty();
    if (est==true)
        cout<<"Âåðøèíû â ãðàôå îòñóòñòâóþò."<<endl;
    else
    {
//îòîáðàæåíèå ìàòðèöû ñìåæíîñòè
        G.PrintGraph(p);

        while (true)
        {
            switch (menu())
            {
                //Ïðîâåðêà ïðèñóòñòâèÿ âåðøèíû â ãðàôå
                case 1: {
                    cout<<"Íàéòè âåðøèíó ";
                    cin>>u;
                    est=G.vertex(u);
                    if (est==false)
                    {cout<<"Âåðøèíà îòñóòñòâóåò."<<endl;}
                    else
                    {cout<<"Âåðøèíà íàéäåíà."<<endl;}
                };
                    break;

                    //Ïðîâåðêà ïðèñóòñòâèÿ ðåáðà ìåæäó âåðøèíàìè â ãðàôå
                case 2: {
                    cout<<"Íàéòè ðåáðî èç âåðøèíû ";
                    cin>>u;
                    cout<<"â âåðøèíó ";
                    cin>>v;
                    est=G.edge(u,v);
                    if (est==false)
                    {cout<<"Ðåáðî îòñóòñòâóåò."<<endl;}
                    else
                    {cout<<"Ðåáðî íàéäåíî."<<endl;}
                };
                    break;

                    //Ïîëó÷åíèå êîëè÷åñòâà âåðøèí
                case 3: {
                    k=G.vertices();
                    cout << "Êîëè÷åñòâî âåðøèí â ãðàôå = "<<k<<endl;
                };
                    break;

                    //Ïîëó÷åíèå êîëè÷åñòâà ðåáåð
                case 4: {
                    k=G.edges();
                    cout << "Êîëè÷åñòâî ðåáåð â ãðàôå = "<<k<<endl;
                };
                    break;

                    //Âû÷èñëåíèå ñòåïåíè âåðøèíû
                case 5: {
                    cout<<"Âåðøèíà: ";
                    cin>>u;
                    est=G.vertex(u);
                    if (est==false)
                    {cout<<"Âåðøèíà îòñóòñòâóåò."<<endl;}
                    else
                    {
                        k=G.out_edges(u);
                        cout<<"Ñòåïåíü âåðøèíû = "<<k<<endl;
                    }
                };
                    break;

                    //Âû÷èñëåíèå ñòåïåíè ðåáðà
                case 6: {
                    cout<<"Ðåáðî èç âåðøèíû ";
                    cin>>u;
                    cout<<"â âåðøèíó ";
                    cin>>v;
                    k=G.s_edge(u,v);
                    if (k==0) cout<<"Ðåáðî îòñóòñòâóåò."<<endl;
                    else cout<<"Ñòåïåíü ðåáðà = "<<k<<endl;
                };
                    break;

                    //Äîáàâëåíèå âåðøèíû
                case 7: {
                    cout<<"Äîáàâèòü âåðøèíó ";
                    cin>>u;
                    G.add_vertex(u);
                    //îòîáðàæåíèå ìàòðèöû ñìåæíîñòè
                    p++;
                    G.PrintGraph(p);
                };
                    break;

                    //Äîáàâëåíèå ðåáðà
                case 8: {
                    cout<<"Äîáàâèòü ðåáðî èç âåðøèíû ";
                    cin>>u;
                    cout<<"â âåðøèíó ";
                    cin>>v;
                    bool est_u=G.vertex(u);
                    bool est_v=G.vertex(v);
                    if (est_u==false || est_v==false)
                    {cout<<"Âåðøèíà îòñóòñòâóåò."<<endl;}
                    else
                    {
                        G.add_edge(u, v);
                        //îòîáðàæåíèå ìàòðèöû ñìåæíîñòè
                        p++;
                        G.PrintGraph(p);
                    }
                };
                    break;

                    //Óäàëåíèå âåðøèíû
                case 9: {
                    cout<<"Óäàëèòü âåðøèíó ";
                    cin>>u;
                    G.del_edges_all(u);//óäàëåíèå âõîäÿùèõ è èñõîäÿùèõ äóã â ìàòðèöå ñìåæíîñòè
                    //G.del_edges_out(u);
                    G.del_edges_in(u);
                    G.del_vertex(u);//óäàëåíèå âåðøèíû èç ñïèñêà âåðøèí
                    //îòîáðàæåíèå ìàòðèöû ñìåæíîñòè
                    p++;
                    G.PrintGraph(p);
                };
                    break;

                    //Óäàëåíèå ðåáðà
                case 10: {
                    cout<<"Óäàëèòü ðåáðî èç âåðøèíû ";
                    cin>>u;
                    cout<<"â âåðøèíó ";
                    cin>>v;
                    G.del_edge(u, v);
                    //îòîáðàæåíèå ìàòðèöû ñìåæíîñòè
                    p++;
                    G.PrintGraph(p);
                };
                    break;
                case 11: return 0;
                default: cout<<"Âûáåðèòå ïðàâèëüíî!"<<endl;
            }
        }
    }
    _getch();
    return 0;
}

