#include <iostream>
#include <cassert>
#include <string>

#include "../include/stack.hpp"
#include "../include/queue.hpp"
#include "../include/PriQueue.hpp"
#include "../include/locations.hpp"
#include "../include/WorkingTechs.hpp"
#include "../include/ITUnit.hpp"
#include "../include/organizer.hpp"
#include "../include/UI.hpp"
#include "../include/FreeTechnicianList.hpp"
#include "../include/WaitingNR.hpp"
#include "../include/WaitingSR.hpp"
#include "../include/WaitingUR.hpp"
#include "../include/Technician.hpp"
#include "../include/request.hpp"

using namespace std;

static int failures = 0;

static void check(bool cond, const string& name) {
    if (cond) {
        cout << "  [PASS] " << name << "\n";
    } else {
        cout << "  [FAIL] " << name << "\n";
        failures++;
    }
}

static void pauseEnd() {
    cout << "\nPress Enter to close...";
    cin.get();
}

int main() {
    cout << "===== PHASE 1.2 DATA STRUCTURE TESTS =====\n";

    // ---------- STACK ----------
    cout << "\n========== STACK TEST ==========\n";
    Stack<int> st;
    cout << "Initial: empty, size=" << st.size() << "\n";
    st.push(10); cout << "Push 10 -> size=" << st.size() << " top=" << st.peek() << "\n";
    st.push(20); cout << "Push 20 -> size=" << st.size() << " top=" << st.peek() << "\n";
    st.push(30); cout << "Push 30 -> size=" << st.size() << " top=" << st.peek() << "\n";
    check(st.pop() == 30, "Pop returns 30");
    cout << "After pop size=" << st.size() << " top=" << st.peek() << "\n";
    check(st.pop() == 20, "Pop returns 20");
    check(st.pop() == 10, "Pop returns 10");
    check(st.isEmpty(), "Stack empty after pops");
    // edge: pop empty
    bool threw = false;
    try { st.pop(); } catch (...) { threw = true; }
    check(threw, "Pop on empty throws");
    cout << "Final Stack Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- QUEUE ----------
    cout << "\n========== QUEUE (FIFO) TEST ==========\n";
    Queue<int> q;
    cout << "Initial: empty, count=" << q.getCount() << "\n";
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    cout << "Enqueued 1,2,3 -> count=" << q.getCount() << "\n";
    int v; q.dequeue(v); check(v == 1, "Dequeue returns 1");
    q.dequeue(v); check(v == 2, "Dequeue returns 2");
    q.dequeue(v); check(v == 3, "Dequeue returns 3");
    check(q.isEmpty(), "Queue empty after dequeues");
    bool dqEmpty = !q.dequeue(v);
    check(dqEmpty, "Dequeue on empty returns false");
    cout << "Final Queue Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- PRIORITY QUEUE ----------
    cout << "\n========== PRIORITY QUEUE TEST ==========\n";
    PriQueue<int> pq;
    pq.enqueue(5); pq.enqueue(1); pq.enqueue(3);
    cout << "Enqueued 5,1,3 -> count=" << pq.getCount() << "\n";
    int p; pq.dequeue(p); check(p == 5, "First dequeue 5 (max default)");
    pq.dequeue(p); check(p == 3, "Second dequeue 3");
    pq.dequeue(p); check(p == 1, "Third dequeue 1");
    check(pq.isEmpty(), "PriQueue empty");
    cout << "Final PriQueue Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- LOCATIONS ----------
    cout << "\n========== LOCATIONS TEST ==========\n";
    Locations loc(3);
    loc.setLocation(1, "CSAI");
    loc.setLocation(2, "LAB1");
    loc.setLocation(3, "ADMIN");
    check(loc.getCount() == 3, "Count == 3");
    check(loc.getLocation(1) == "CSAI", "loc1 CSAI");
    check(loc.getLocation(2) == "LAB1", "loc2 LAB1");
    check(loc.getLocation(3) == "ADMIN", "loc3 ADMIN");
    check(loc.getLocation(4) == "", "out-of-range returns empty");
    cout << "Final Locations Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- WORKINGTECHS ----------
    cout << "\n========== WORKINGTECHS TEST ==========\n";
    Request r1(20, 1, 1, 1, NR, 0);
    Request r2(30, 1, 1, 1, NR, 0);
    Request r3(10, 1, 1, 1, NR, 0);
    r1.setFT(8); r2.setFT(5); r3.setFT(5);
    Technician t1(1, "GT"), t2(2, "GT"), t3(3, "GT");
    t1.assign(&r1); t2.assign(&r2); t3.assign(&r3);
    WorkingTechs working;
    working.enqueue(&t1); working.enqueue(&t2); working.enqueue(&t3);
    cout << "Enqueued t1,t2,t3 -> "; working.print();
    Technician* fin;
    working.dequeue(fin); check(fin->getID() == 3, "First dequeued ID 3 (FT5,RID10)");
    working.dequeue(fin); check(fin->getID() == 2, "Second dequeued ID 2 (FT5,RID30)");
    working.dequeue(fin); check(fin->getID() == 1, "Third dequeued ID 1 (FT8)");
    check(working.isEmpty(), "WorkingTechs empty");
    cout << "Final WorkingTechs Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- WAITINGNR ----------
    cout << "\n========== WAITINGNR CANCEL TEST ==========\n";
    WaitingNR wnr;
    Request a(1,1,1,1,NR,0), b(2,1,1,1,NR,0), c(3,1,1,1,NR,0);
    wnr.enqueue(&a); wnr.enqueue(&b); wnr.enqueue(&c);
    cout << "Enqueued RIDs 1,2,3 -> count=" << wnr.getCount() << "\n";
    Request* cancelled = wnr.cancelByRID(2);
    check(cancelled != nullptr && cancelled->getRID() == 2, "Cancel RID 2 returns request 2");
    check(wnr.getCount() == 2, "Count after cancel == 2");
    Request* none = wnr.cancelByRID(999);
    check(none == nullptr, "Cancel nonexistent RID returns null");
    // remove first and last
    Request* firstR = wnr.cancelByRID(1);
    check(firstR != nullptr && firstR->getRID() == 1, "Cancel first element (RID1)");
    Request* lastR = wnr.cancelByRID(3);
    check(lastR != nullptr && lastR->getRID() == 3, "Cancel last element (RID3)");
    check(wnr.isEmpty(), "WaitingNR empty after cancels");
    cout << "Final WaitingNR Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- WAITINGSR ----------
    cout << "\n========== WAITINGSR FIFO TEST ==========\n";
    WaitingSR wsr;
    Request s1(5,1,1,1,SR,0), s2(6,1,1,1,SR,0);
    wsr.enqueue(&s1); wsr.enqueue(&s2);
    cout << "Enqueued SR 5,6 -> count=" << wsr.getCount() << "\n";
    Request* sr;
    wsr.dequeue(sr); check(sr->getRID() == 5, "First dequeue RID 5");
    wsr.dequeue(sr); check(sr->getRID() == 6, "Second dequeue RID 6");
    check(wsr.isEmpty(), "WaitingSR empty");
    cout << "Final WaitingSR Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- FREE TECH LIST ----------
    cout << "\n========== FREETECHNICIANLIST TEST ==========\n";
    FreeTechnicianList freeGT;
    Technician g1(2,"GT"), g2(1,"GT"), g3(3,"GT");
    freeGT.insert(&g1); freeGT.insert(&g2); freeGT.insert(&g3);
    cout << "Inserted GTs 2,1,3 -> "; freeGT.print();
    Technician* removed = freeGT.remove();
    check(removed != nullptr && removed->getID() == 1, "Remove min ID (1)");
    removed = freeGT.remove();
    check(removed != nullptr && removed->getID() == 2, "Remove next (2)");
    removed = freeGT.remove();
    check(removed != nullptr && removed->getID() == 3, "Remove next (3)");
    check(freeGT.isEmpty() && freeGT.remove() == nullptr, "Remove on empty returns null");
    cout << "Final FreeTechnicianList Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- WAITINGUR ----------
    cout << "\n========== WAITINGUR PRIORITY TEST ==========\n";
    WaitingUR wur;
    Request u1(10, 5, 1, 1, UR, 1);
    Request u2(20, 3, 1, 1, UR, 9);
    Request u3(30, 4, 1, 1, UR, 9);
    wur.enqueue(&u1); wur.enqueue(&u2); wur.enqueue(&u3);
    cout << "Enqueued URs (RID10 PR1 QT5, RID20 PR9 QT3, RID30 PR9 QT4)\n";
    Request* first; wur.dequeue(first); check(first->getRID() == 20, "First: RID20 (PR9, QT3)");
    Request* second; wur.dequeue(second); check(second->getRID() == 30, "Second: RID30 (PR9, QT4)");
    Request* third; wur.dequeue(third); check(third->getRID() == 10, "Third: RID10 (PR1)");
    check(wur.isEmpty(), "WaitingUR empty");
    cout << "Final WaitingUR Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- EQUAL PRIORITY / DUPLICATES ----------
    cout << "\n========== EQUAL PRIORITY TEST ==========\n";
    WaitingUR wur2;
    Request e1(1, 2, 1, 1, UR, 5);
    Request e2(2, 2, 1, 1, UR, 5);
    wur2.enqueue(&e1); wur2.enqueue(&e2);
    Request* ep; wur2.dequeue(ep); check(ep->getRID() == 1, "Equal PR/QT: smaller RID first");
    wur2.dequeue(ep); check(ep->getRID() == 2, "Second dequeued RID 2");
    cout << "Final Equal Priority Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- REQUEST ----------
    cout << "\n========== REQUEST TEST ==========\n";
    Request rq(7, 5, 3, 2, UR, 9);
    check(rq.getRID() == 7, "getRID");
    check(rq.getQT() == 5, "getQT");
    check(rq.getLID() == 3, "getLID");
    check(rq.getPC() == 2, "getPC");
    check(rq.getPR() == 9, "getPR");
    check(rq.getType() == UR, "getType");
    check(rq.getStatus() == WAITING, "getStatus initial");
    rq.setRID(8); rq.setQT(6); rq.setLID(4); rq.setPC(3); rq.setPR(7);
    rq.setAT(1); rq.setST(2); rq.setFT(5); rq.setType(NR); rq.setStatus(COMPLETED);
    check(rq.getRID() == 8 && rq.getQT() == 6 && rq.getLID() == 4 && rq.getPC() == 3, "setters basic");
    check(rq.getPR() == 7 && rq.getAT() == 1 && rq.getST() == 2 && rq.getFT() == 5, "setters times");
    check(rq.getType() == NR && rq.getStatus() == COMPLETED, "setType/setStatus");
    cout << "Final Request Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- TECHNICIAN ----------
    cout << "\n========== TECHNICIAN TEST ==========\n";
    Technician tech(5, "ST");
    check(tech.getID() == 5, "getID");
    check(tech.isST(), "isST true");
    check(tech.getBusyTime() == 0, "busyTime initial 0");
    check(tech.getCurrentRequest() == nullptr, "currentRequest initial null");
    Request rr(99, 1, 1, 1, NR, 0);
    tech.assign(&rr);
    check(tech.getCurrentRequest() == &rr, "assign sets currentRequest");
    tech.complete();
    check(rr.getStatus() == COMPLETED, "complete sets request COMPLETED");
    check(tech.getCurrentRequest() == nullptr, "complete clears currentRequest");
    Technician tech2(6, "GT");
    check(!tech2.isST(), "GT isST false");
    tech2.assign(&rr);
    tech2.cancelCurrentRequest();
    check(rr.getStatus() == CANCELLED, "cancelCurrentRequest sets CANCELLED");
    check(tech2.getCurrentRequest() == nullptr, "cancel clears currentRequest");
    cout << "Final Technician Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- ITUNIT ----------
    cout << "\n========== ITUNIT TEST ==========\n";
    ITUnit unit(1, 2);
    check(unit.getFreeST() != nullptr, "getFreeST returns technician");
    check(unit.getFreeGT() != nullptr, "getFreeGT returns technician");
    Request nrq(200, 1, 1, 1, NR, 0);
    unit.addWaitingNR(&nrq);
    check(unit.getWaitingNRCount() == 1, "addWaitingNR count 1");
    Request* got = unit.getWaitingNR();
    check(got == &nrq, "getWaitingNR returns same pointer");
    check(unit.getWaitingNRCount() == 0, "count after dequeue 0");
    Request srq(201, 1, 1, 1, SR, 0), urq(202, 1, 1, 1, UR, 5);
    unit.addWaitingSR(&srq);
    unit.addWaitingUR(&urq);
    check(unit.getWaitingSRCount() == 1, "WaitingSR count 1");
    check(unit.getWaitingURCount() == 1, "WaitingUR count 1");
    check(unit.getWaitingSR() == &srq, "getWaitingSR pointer");
    check(unit.getWaitingUR() == &urq, "getWaitingUR pointer");
    cout << "Final ITUnit Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- ORGANIZER ----------
    cout << "\n========== ORGANIZER TEST ==========\n";
    Organizer org;
    org.loadSampleData();
    cout << "Organizer loadSampleData OK\n";
    cout << "Final Organizer Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    // ---------- UI ----------
    cout << "\n========== UI TEST ==========\n";
    UI ui;
    check(ui.isInteractive() == true, "default interactive true");
    cout << "UI constructor OK\n";
    cout << "Final UI Test: " << (failures == 0 ? "PASS" : "FAIL") << "\n";

    cout << "\n===== TOTAL FAILURES: " << failures << " =====\n";
    pauseEnd();
    return 0;
}