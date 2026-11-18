#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
using namespace std;

// Type of request: Normal, Special, or Urgent
enum RequestType { NR, SR, UR };

enum RequestStatus { WAITING, IN_SERVICE, COMPLETED, CANCELLED };

class Request {
private:
    int RID;              // request ID
    int QT;               // arrival time into queue
    int LID;              // location ID
    int PC;               // type of problem code
    RequestType type;
    RequestStatus status;
    int PR;               // priority for UR
    int AT;               // time request is assigned
    int ST;               // service start time
    int FT;               // service finish time

public:
    Request(int rid, int qt, int lid, int pc, RequestType t, int pr) {
        RID    = rid;
        QT     = qt;
        LID    = lid;
        PC     = pc;
        type   = t;
        PR     = pr;
        AT     = 0;
        ST     = 0;
        FT     = 0;
        status = WAITING;
    }

    int getRID()               const { return RID; }
    int getQT()                const { return QT; }
    int getLID()               const { return LID; }
    int getPC()                const { return PC; }
    int getPR()                const { return PR; }
    int getAT()                const { return AT; }
    int getST()                const { return ST; }
    int getFT()                const { return FT; }
    RequestType getType()      const { return type; }
    RequestStatus getStatus()  const { return status; }

    void setRID(int rid)               { RID = rid; }
    void setQT(int qt)                 { QT = qt; }
    void setLID(int lid)               { LID = lid; }
    void setPC(int pc)                 { PC = pc; }
    void setPR(int pr)                 { PR = pr; }
    void setAT(int at)                 { AT = at; }
    void setST(int st)                 { ST = st; }
    void setFT(int ft)                 { FT = ft; }
    void setType(RequestType t)        { type = t; }
    void setStatus(RequestStatus s)    { status = s; }

    friend ostream& operator<<(ostream& os, const Request& req) {
        os << "\n      ID:                  " << req.RID    << "\n"
           << "      Queue Time:          " << req.QT     << "\n"
           << "      Location:            " << req.LID    << "\n"
           << "      Type of Code:        " << req.PC     << "\n"
           << "      Time of Assignment:  " << req.AT     << "\n"
           << "      Service Time:        " << req.ST     << "\n"
           << "      Finish Time:         " << req.FT     << "\n"
           << "      Type:                " << req.type   << "\n"
           << "      Status:              " << req.status << "\n";
        return os;
    }
    friend ostream& operator<<(ostream& os, const Request* req) {
        if (req != nullptr) {
            os << "\n      ID:                  " << req->RID    << "\n"
               << "      Queue Time:          " << req->QT     << "\n"
               << "      Location:            " << req->LID    << "\n"
               << "      Type of Code:        " << req->PC     << "\n"
               << "      Time of Assignment:  " << req->AT     << "\n"
               << "      Service Time:        " << req->ST     << "\n"
               << "      Finish Time:         " << req->FT     << "\n"
               << "      Type:                " << req->type   << "\n"
               << "      Status:              " << req->status << "\n";
        } else {
            os << "null";
        }
        return os;
    }
};

#endif
