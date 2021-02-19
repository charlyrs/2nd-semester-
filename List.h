#pragma once

#include <string>
#include <exception>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <iterator>

#include <fstream>

#include <regex>

enum status {
    STUDENT = 0, MAGISTRANT
};

class Participant {
    std::string surname;
    std::string name_and_middlename;
    std::string status;
    int course;
    std::string id;
public:
    Participant(std::string sn, std::string n, std::string st, int c, std::string id) {
        surname = sn;
        name_and_middlename = n;
        status = st;
        course = c;
        this->id = id;
    }

    Participant() {
        surname = " ";
        name_and_middlename = " ";
        status = " ";
        course = 0;
        id = " ";
    }

    Participant &operator=(const Participant &other) {
        if (this == &other) return *this;
        surname = other.surname;
        name_and_middlename = other.name_and_middlename;
        status = other.status;
        course = other.course;
        id = other.id;
        return *this;
    }

    std::string Surname() const { return surname; }

    std::string Name() const { return surname + " " + name_and_middlename; }

    int Course() const { return course; }

    std::string ID() const { return id; }

    std::string Status() const { return status; }
};

typedef std::vector<std::shared_ptr<std::string>> container;
typedef std::vector<std::string> vector;
std::ostream& Output(std::ostream& out, std::shared_ptr<std::string> item){
    out << *item;
    return out;
}

class List {
private:
    container list;

    static void FixLine(std::string &line) {
        std::regex expr(
                "([a-zA-Z\\']+)(\\d+)([a-zA-Z\\']+)(\\d+)([a-zA-Z\\']+)(\\d+)(\\D+)(\\d+)(\\d)(\\D+)(\\d+)(\\d{8})");
        std::regex_constants::match_flag_type flag = {};
        line = std::regex_replace(line, expr, "$1 $3 $5 $7 $9 kursa $12", flag);
    }

public:
    Participant ToParticipant(std::string line) const {
        std::stringstream ss;
        ss << line;
        std::string surname;
        ss >> surname;
        std::string othername;
        ss >> othername;
        std::string temp;
        ss >> temp;
        othername += " ";
        othername += temp;
        std::string status;
        ss >> status;
        int course;
        ss >> course;
        std::string id;
        ss >> id;
        ss >> id;
        return Participant(surname, othername, status, course, id);
    }

public:

    friend std::istream &operator>>(std::istream &input, List &a) {
        vector temp;
        std::copy(
                std::istream_iterator<std::string, char>(input),
                std::istream_iterator<std::string, char>(),
                std::back_inserter(temp));
        for (auto x : temp) {
            a.list.push_back(std::make_shared<std::string>(x));
        }
        a.FixLines();
        return input;
    }

    void FixLines() {
        for (auto &x : list) {
            FixLine(*x);
        }
    }

    void FilterByCourse(int minCourse) {
        auto newEnd = std::remove_if(list.begin(), list.end(), [&minCourse, this](const std::shared_ptr<std::string> &item) {
            Participant temp;
            temp = ToParticipant(*item);
            return temp.Course() < minCourse;
        });
        list.erase(newEnd,list.end());
    }
    void Sort(){
        std::sort(list.begin(), list.end(),[this](const std::shared_ptr<std::string> &item1, const std::shared_ptr<std::string> &item2){
            auto first = ToParticipant(*item1);
            auto second = ToParticipant(*item2);
            if(first.Surname()==second.Surname()){
                return first.Name()<second.Name();
            }
            return first.Surname()<second.Surname();
        });
    }

    std::vector<std::string> ToVector() const {
        std::vector<std::string> result;
        for (auto x : list) {
            result.push_back(*x);
        }
        return result;
    }

    void ToConcole(){
        typename std::iterator_traits<std::shared_ptr<std::string>> it;

        std::copy ( list.begin(), list.end(),std::ostream_iterator<std::shared_ptr<std::string>,char> (Output(std::cout),"\n") );
    }

};