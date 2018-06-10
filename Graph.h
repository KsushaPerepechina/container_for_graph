#include <vector>
#include <set>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//îðèåíòèðîâàííûé ãðàô, ïðåäñòàâëåííûé ìàòðèöåé ñìåæíîñòè
template<class T> class Graph
{
//**********************************************
    template<class T>
    class __iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
    private:
        pointer pos_;

    public:
        /// @ Êîíñòðóêòîðû è îïåðàòîðû íåîáõîäèìûå äëÿ òîãî, ÷òîáû
        ///       èòåðàòîð ñîîòâåòñòâîâàë êîíöåïöèÿì InputIterator (âõîäíîé èòåðàòîð),
        ///       OuputIterator (âûõîäíîé èòåðàòîð), ForwardIterator (îäíîíàïðàâëåííûé èòåðàòîð).
        __iterator()
                : pos_(0)
        {
        }

        explicit __iterator(pointer pos)
                : pos_(pos)
        {
        }

        explicit __iterator(const __iterator &it)
                : pos_(it.pos_)
        {
        }

        __iterator &operator=(const __iterator &it)
        {
            pos_ = it.pos_;
        }

        __iterator &operator++()
        {
            ++pos_;
            return *this;
        }

        __iterator operator++(int)
        {
            __iterator tmp(*this);
            operator++();
            return tmp;
        }

        bool operator==(const __iterator &it)
        {
            return pos_ == it.pos_;
        }

        bool operator!=(const __iterator &it)
        {
            return pos_ != it.pos_;
        }

        reference operator*()
        {
            return *pos_;
        }

        pointer operator->()
        {
            return pos_;
        }
        /// @}

        /// Îïåðàòîðû íåîáõîäèìûå äëÿ òîãî, ÷òîáû èòåðàòîð ñîîòâåòñòâîâàë êîíöåïöèè
        ///       BidirectionalIterator (äâóíàïðàâëåííûé èòåðàòîð).
        __iterator &operator--()
        {
            --pos_;
            return *this;
        }

        __iterator operator--(int)
        {
            __iterator tmp(*this);
            operator--();
            return tmp;
        }
        /// @}

        /// @ Îïåðàòîðû íåîáõîäèìûå äëÿ òîãî, ÷òîáû èòåðàòîð ñîîòâåòñòâîâàë êîíöåïöèè
        ///       RandomAccessIterator (èòåðàòîð ïðîèçâîëüíîãî äîñòóïà).
        /// @{
        reference operator[](const difference_type &n)
        {
            return pos_[n];
        }

        __iterator &operator+=(const difference_type &n)
        {
            pos_ += n;
            return *this;
        }

        __iterator operator+(const difference_type &n)
        {
            return __iterator(pos_ + n);
        }

        __iterator &operator-=(const difference_type &n)
        {
            pos_ -= n;
            return *this;
        }

        __iterator operator-(const difference_type &n)
        {
            return __iterator(pos_ - n);
        }

        bool operator<(const __iterator &it)
        {
            return pos_ < it.pos_;
        }

        bool operator>(const __iterator &it)
        {
            return pos_ > it.pos_;
        }

        bool operator<=(const __iterator &it)
        {
            return pos_ <= it.pos_;
        }

        bool operator>=(const __iterator &it)
        {
            return pos_ >= it.pos_;
        }
        /// @}
    };

/// Ïðåäëàãàåìûå ñòàíäàðòíûå typedef'û.
/// @{
    typedef T          value_type;

    typedef value_type*     pointer;
    typedef const pointer   const_pointer;

    typedef value_type&     reference;
    typedef const reference const_reference;

    typedef __iterator<T>   iterator;

    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;
/// @}

//**********************************************
public:
    typedef  T Vertex;//âåðøèíà
private:
    //Äëÿ îïèñàíèÿ ñîñåäíèõ (ñìåæíûõ) âåðøèí óäîáíåå èñïîëüçîâàòü áèáëèîòå÷íûé êëàññ set, ÷åì list.
    typedef std::set<Vertex> Adjacency;
    //Ïðåäñòàâëåíèå ìàòðèöû ñìåæíîñòè - ìàññèâ (vector) ñïèñêîâ ñìåæíûõ âåðøèí (âåðøèíà, ñïèñîê ñìåæíûõ âåðøèí).
    typedef std::vector<set<Vertex>> Matrica;
    Matrica matrica;
    //âåðøèíû
    typedef std::vector<Vertex> Ver;
    Ver ver;
public:
    //Ýëåìåíòàðíûé êîíñòðóêòîð, ïîçâîëÿþùèé ñðàçó çàäàòü êîëè÷åñòâî âåðøèí â ãðàôå (ïî óìîë÷àíèþ - íîëü).
    explicit Graph(size_type vertices_ = 0u, const T& value = T()) : matrica(vertices_)
    {
    };
    // Äåñòðóêòîð.
    ~Graph()
    {
        for(unsigned i = 0;i < matrica.size();i++)
        {matrica[i].clear();
        }
    }

    //Åñòü ëè âåðøèíû â ãðàôå?
    bool empty() const
    {
        return matrica.empty();
    }

    //Ñêîëüêî âåðøèí â ãðàôå?
    std::size_t vertices() const
    {
        return ver.size();
    }

    //Ñêîëüêî ð¸áåð â ãðàôå?
    std::size_t edges() const
    {
        std::size_t res = 0u;
        for (Matrica::const_iterator p = matrica.begin();
             p != matrica.end(); ++p)
            res += p->size();
        return res;
    }

    //Åñòü ëè ðåáðî (äóãà) èç u â v?
    bool edge(Vertex u, Vertex v) const
    {
        const T verts = vertices();
        if (u < verts && v < verts)
            return matrica[u].find(v) != matrica[u].end();
        return false;
    }

    //Ñîçäàòü âåðøèíó u.
    void add_vertex(Vertex u)
    {
        ver.push_back(u);
    }

    //Åñòü ëè âåðøèíà u?
    bool vertex(Vertex u) const
    {
        bool a=false;
        for (unsigned p = 0; p < ver.size(); p++)
        {
            if (ver[p]==u)
                a=true;
        };
        return a;
    }

    //Ñîçäàòü ðåáðî èç u â v.
    void add_edge(Vertex u, Vertex v)
    {
        const T verts = vertices();
        if (u < verts && v < verts)
            matrica[u].insert(v);
    }

    //Ñîçäàòü ð¸áðà èç u â v è èç v â u.
    void add_edge_bi(Vertex u, Vertex v)
    {
        const T verts = vertices();
        if (u < verts && v < verts)
        {
            matrica[u].insert(v);
            matrica[v].insert(u);
        }
    }

    //Óäàëèòü âåðøèíó.
    void del_vertex(Vertex u)
    {
        //const T item = ver.back();
        for (unsigned p = 0; p < ver.size(); p++)
        {
            if (ver[p]==u)
            {
                const T item = /*ver[ver.size()-1]*/ver.back();
                // Óäàëÿåì ïîñëåäíèé ýëåìåíò èç ìàññèâà vector
                ver.pop_back();
                // Âñòàâëÿåì ñîõðàíåííûé ýëåìåíò âìåñòî ýëåìåíòà ñ èíäåêñîì p
                if (p<ver.size())
                {ver[p] = item;}
            }
        }
    }

    //Óäàëèòü ðåáðî.
    void del_edge(Vertex u, Vertex v)
    {
        const T verts = vertices();
        if (u < verts && v < verts)
            matrica[u].erase(v);
    }

    //Óäàëèòü ð¸áðà èç u â v è èç v â u.
    void del_edge_bi(Vertex u, Vertex v)
    {
        const T verts = vertices();
        if (u < verts && v < verts)
        {
            matrica[u].erase(v);
            matrica[v].erase(u);
        }
    }

    //Còåïåíü ðåáðà.
    int s_edge(Vertex u, Vertex v)
    {
        int s;
        bool est;
        est=edge(u, v);
        if (est==false) {s=0;}
        else
        {
            if (v==u) {s=1;} //ïåòëÿ
            else s=2;
        }
        return s;
    }

    //Ñòåïåíü âåðøèíû - êîëè÷åñòâî èñõîäÿùèõ ð¸áåð.
    /*std::size_t*/T out_edges(Vertex u) const
    {
        const T verts = vertices();
        return u < /*vertices()*/verts? matrica[u].size(): 0u;
    }

    //Óäàëèòü âñå ð¸áðà, èñõîäÿùèå èç v. (Ñäåëàòü ýòó âåðøèíó "ñòîêîì".)
    void del_edges_out(Vertex v)
    {
        const T verts = vertices();
        if (v < verts)
            matrica[v].clear();
    }

    //Óäàëèòü âñå ð¸áðà, âõîäÿùèå â v. (Ñäåëàòü ýòó âåðøèíó "èñòî÷íèêîì".)
    void del_edges_in(Vertex v)
    {
        const T verts = vertices();
        if (v < verts)
        {
            for (Matrica::iterator p = matrica.begin(), end = matrica.end();
                 p != end; ++p)
                p->erase(v);
        }
    }

    //Óäàëèòü âîîáùå âñå ð¸áðà, èíöèäåíòíûå v.
    void del_edges_all(Vertex v)
    {
        del_edges_out(v);
        del_edges_in(v);
    }

    //Äâóíàïðàâëåííûé èòåðàòîð äëÿ ïåðåáîðà âåðøèí
    //Äâóíàïðàâëåííûé èòåðàòîð äëÿ ïåðåáîðà ðåáåð
    //Äâóíàïðàâëåííûé èòåðàòîð äëÿ ïåðåáîðà ðåáåð, èíöèäåíòíûõ âåðøèíå
    //Äâóíàïðàâëåííûé èòåðàòîð äëÿ ïåðåáîðà âåðøèí, ñìåæíûõ âåðøèíå
    //Óäàëåíèå âåðøèíû ïî èòåðàòîðó íà âåðøèíó
    //Óäàëåíèå ðåáðà ïî èòåðàòîðó íà ðåáðî
    //Êîíñòàíòíûå ìîäèôèêàöèè äëÿ âñåõ èòåðàòîðîâ
    //Îáðàòíûå ìîäèôèêàöèè äëÿ èòåðàòîðîâ
    void revers_all(Vertex v)
    {
        cout << "Ñìåæíûå âåðøèíû â îáðàòíîì ïîðÿäêå:" << endl;
        for (Adjacency::reverse_iterator i=matrica[v].rbegin(); i!=matrica[v].rend(); i++)
        {
            cout<<*i<<" ";
        }
        cout<<endl;
    }

    //Îòîáðàæåíèå ìàòðèöû ñìåæíîñòè
    //Îòîáðàæåíèå ãðàôà â âèäå pdf- ôàéëà, ñîçäàííîãî ñ ïîìîùüþ Graphviz 2.39.
    //Graphviz ýòî ïðîãðàììà, êîòîðàÿ ïîçâîëÿåò ñîçäàâàòü ðàçëè÷íûå òèïû ãðàôèêîâ, èñïîëüçóÿ ÿçûê ðàçìåòêè DOT.
    //×òîáû ýòî ðàáîòàëî, íåîáõîäèìî óñòàíîâèòü Graphviz, ïðîïèñàòü â Path (ïåðåìåííûå ñðåäû â ñâ-âàõ êîìïüþòåðà) ïóòü ê Graphviz:
    //C:\Program Files\Graphviz2.39\bin - äëÿ ôîðìèðîâàíèÿ dot-ôàéëà ñ ïîìîùüþ dot.exe
    void PrintGraph (int p0)
    {
        char string1[6] = "";
        char string2[6] = "";
        FILE * fo;
        fo = fopen("d:\\g.dot","wt");//ôîðìèðîâàíèå ôàéëà g.dot
        if (fo) // åñëè åñòü äîñòóï ê ôàéëó
        {
            fputs("digraph Graph {\n", fo);//1-àÿ ñòðîêà â ôàéëå g.dot

            bool est=false;
            // for (unsigned int i=0;i<matrica.size();i++)
            for (unsigned int p55 = 0; p55 < ver.size(); p55++)
            {
                unsigned int i=ver[p55];
                itoa(i, string1, 10);
                est=false;
                for (Adjacency::const_iterator
                             p = matrica[i].begin(), end = matrica[i].end(); p != end; ++p)
                {
                    //	bool est31=vertex(*p);// âåðøèíà ñóùåñòâóåò
                    //if (est31==true)
                    //{
                    cout<<i<<"->"<<*p<<" ";
                    est=true;
                    //ñòðîêè â ôàéëå g.dot â âèäå: âåðøèíà->âåðøèíà
                    fputs(string1, fo);
                    fputs("->", fo);

                    itoa(*p, string2, 10);
                    fputs(string2, fo);
                    fputs("\n", fo);
                    //}
                }
                if (est==true) cout<<endl;
                else //íåò äóã, îäèíî÷íàÿ âåðøèíà
                {
                    bool est3=vertex(i);// âåðøèíà ñóùåñòâóåò
                    if (est3==true)
                    {cout<<i<<endl;
                        fputs(string1, fo);//ñòðîêè â ôàéëå g.dot â âèäå: âåðøèíà
                        fputs("\n", fo);}
                }
            }
            fputs("}", fo);//ïîñëåäíÿÿ ñòðîêà â ôàéëå g.dot
        }
        else
            cout << "Íåò äîñòóïà ê ôàéëó!" << endl;
        fclose(fo);
        //âûïîëíåíèå êîìàíäû èç cmd
        char name_com[200];
        strcpy_s(name_com,"dot -Kfdp -Tpng d:\\g.dot > d:\\");// png
        char string[6] = "";
        itoa(p0, string, 10);//äîáàâèòü â íà÷àëî èìåíè ôàéëà íîìåð (p0)
        strcat_s(name_com, string);
        strcat_s(name_com, "g.png");
        system(name_com);//çàïóñê êîìàíäû èç cmd "dot -Kfdp -Tpng d:\\g.dot > d:\\g.png"
        cout<<"Ñîçäàí ôàéë "<<p0<<"g.png"<<endl<<endl;
    }
};

