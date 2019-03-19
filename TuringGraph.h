//
// Created by BugenZhao on 2019/3/3.
//

#ifndef DATASTRUCTURE_TURINGGRAPH_H
#define DATASTRUCTURE_TURINGGRAPH_H

#include <string>
#include <vector>

struct Author {
    int no;
    std::string name;
    int birthYear;
    int awardYear;
    int publicationCount;
};

struct Cooperation {
    int year;
    std::string content;
};

class TuringGraph {

private:
    int authorN;
    Author *authors;
    std::vector<Cooperation> **cooperations;

    int currentYear;


public:
    TuringGraph();

    TuringGraph(int year);

    const Author &getAuthor(const std::string &name);

    const Author &getAuthor(int no);

    const std::vector<Cooperation> &getCooperations(const Author &a, const Author &b);

    const std::vector<Cooperation> &getCooperations(const std::string &a, const std::string &b);

    const std::vector<Cooperation> &getCooperations(int a, int b);

    void setYear(int year);

    void drawGraph();

    ~TuringGraph();
};


#endif //DATASTRUCTURE_TURINGGRAPH_H
