#pragma once

#include <string>
#include <exception>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <sstream>
#include <set>
#include <iterator>
#include <unordered_set>
#include <fstream>
#include <regex>


struct Participant {
    std::string surname;
    std::string name;
    std::string middle_name;
    std::string status;
    int course;
    std::string id;

    Participant() {
        surname = " ";
        name = " ";
        middle_name = " ";
        status = " ";
        course = 0;
        id = " ";
    }

    std::string NameAndMiddleName() const {
        return name + " " + middle_name;
    }

    std::string FullName() const {
        return surname + " " + name + " " + middle_name;
    };

    std::string Info() const {
        return surname + " " + name + " " + middle_name + " student " + std::to_string(course) + " kursa " + id;
    }

    friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Participant> &a) {
        out << a->Info();
        return out;
    }

    friend std::ostream &operator<<(std::ostream &out, const Participant &a) {
        out << a.Info();
        return out;
    }
};

struct Compare {
    bool operator()(const std::shared_ptr<Participant> &first, const std::shared_ptr<Participant> &second) const {
        return first->FullName() == second->FullName();
    }
};

struct Hash {
    std::size_t operator()(std::shared_ptr<Participant> const &a) const noexcept {
        size_t hash = 0;
        for (auto x : a->FullName()) {
            hash += x;
        }
        return hash;
    }
};

class List {
private:

    std::vector<std::shared_ptr<Participant>> list;

    static void FixLine(std::string &line) {
        std::regex expr(
                R"(([a-zA-Z\']+)(\d+)([a-zA-Z\']+)(\d+)([a-zA-Z\']+)(\d+)(\D+)(\d+)(\d)(\D+)(\d+)(\d{8}))");

        if (!std::regex_match(line, expr)) throw std::invalid_argument("Not a participant");
        //std::regex_constants::match_flag_type flag = {};
        line = std::regex_replace(line, expr, "$1 $3 $5 $7 $9 kursa $12");

    }

    static void FixLines(std::vector<std::string> &l) {
        for (auto &x : l) {
            FixLine(x);
        }
    }

public:
    static Participant ToParticipant(const std::string &line) {
        Participant participant;
        std::stringstream ss;
        ss << line;
        ss >> participant.surname >> participant.name >> participant.middle_name >>
           participant.status >> participant.course;
        ss >> participant.id;
        ss >> participant.id;
        return participant;
    }

    friend std::istream &operator>>(std::istream &input, List &a) {
        std::vector<std::string> temp;
        std::copy(
                std::istream_iterator<std::string, char>(input),
                std::istream_iterator<std::string, char>(),
                std::back_inserter(temp));
        FixLines(temp);
        for (auto x : temp) {
            a.list.push_back(std::make_shared<Participant>(ToParticipant(x)));
        }
        return input;
    }

    void FilterByCourse(const int &minCourse) {
        if (minCourse == 1) return;
        auto newEnd = std::remove_if(list.begin(), list.end(),
                                     [&minCourse](const std::shared_ptr<Participant> &item) {
                                         return item->course < minCourse;
                                     });
        list.erase(newEnd, list.end());
    }

    void Sort() {
        std::sort(list.begin(), list.end(),
                  [](const std::shared_ptr<Participant> &first, const std::shared_ptr<Participant> &second) {
                      if (first->surname == second->surname) {
                          return first->NameAndMiddleName() < second->NameAndMiddleName();
                      }
                      return first->surname < second->surname;
                  });
    }

    // I have used it for testing my program
    std::vector<std::string> ToVector() const {
        std::vector<std::string> result;
        for (auto x : list) {
            result.push_back(x->Info());
        }
        return result;
    }

    void ToConcole() {
//        std::ostream_iterator<Participant> it(std::cout,"\n");
//        std::transform(list.begin(),list.end(),it,
//                       [](std::shared_ptr<Participant> item){return *item;});

//        works the same way
        std::copy(list.begin(), list.end(),
                  std::ostream_iterator<std::shared_ptr<Participant>>(std::cout, "\n"));
    }

    auto ToSet() {
        std::unordered_set<std::shared_ptr<Participant>, Hash, Compare> set;
        for (auto x : list) {
            set.insert(x);
        }
        return set;
    }
};

class Program {
public:
    void Run() {
        std::fstream fin("input.txt");
        List list;
        if (!fin.is_open()) {
            std::cout << "File is not opened\n";
            std::exit(11);
        }
        fin >> list;
        fin.close();
        std::cout << "Enter minimum course\n";
        int min_course;
        std::cin >> min_course;
        if (min_course < 1 || min_course > 4) throw std::invalid_argument("Wrong input");
        list.FilterByCourse(min_course);
        list.Sort();
        list.ToConcole();
        auto set = list.ToSet();
        std::string temp;
        while (getline(std::cin, temp)) {
            if (temp == "end") break;
            auto it = set.find(std::make_shared<Participant>(list.ToParticipant(temp)));
            //I've changed Compare and Hash so that they use only full name to get the result
            //so .find() works properly with "full_name" provided
            if (it == set.end()) {
                std::cout << "There is no such person in the list\n";
                continue;
            }
            std::cout << (*it)->id << '\n';

        }


    }
};