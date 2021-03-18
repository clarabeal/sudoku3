#ifndef _CASE_H
#define _CASE_H

class Case {
    public:

    bool modifiable;

    Case (unsigned int l, unsigned int c, unsigned int carre, unsigned int val, bool modifiable);

    unsigned int getL ();

    unsigned int getC ();

    unsigned int getCarre ();

    unsigned int getVal ();

    void setVal ();

    private:

    unsigned int val, l, c, carre;
};

#endif