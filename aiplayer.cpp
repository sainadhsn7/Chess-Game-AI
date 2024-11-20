 #include "aiplayer.h"
#include "fennotation.h"
#include <QThread>
#include <QTimer>
#include <QTime>
#include <bookcreator.h>

AIPlayer::AIPlayer(Board *board, AISettings *settings, QObject *parent)
    : Player(parent), moveFound(false) {
    this->board = board;
    this->settings = settings;
    search = new Search(board, settings, this);
    move = new Move(0);
    // book = new Book(BookCreator::loadBookFromFile(settings->book));

    // connect(settings, &AISettings::requestAbortSearch, this, &AIPlayer::timeOutThreadedSearch);
    connect(search, &Search::onSearchComplete, this, &AIPlayer::onSearchComplete);

    cancelSearchTimer = new QTimer(this);
    cancelSearchTimer->setSingleShot(true);
    connect(cancelSearchTimer, &QTimer::timeout, this, &AIPlayer::timeOutThreadedSearch);
}
AIPlayer::~AIPlayer(){
    delete move;
    delete search;
}
void AIPlayer::Update() {
    // return;
    if (moveFound) {
        moveFound = false;
        ChoseMove(*move);
    }
    // settings->diagnostics = search->searchDiagnostics;
}

void AIPlayer::NotifyTurnToMove() {
    // search->searchDiagnostics.isBook = false;
    moveFound = false;
    Move bookMove(0);
    // if (settings->useBook && board->plyCount <= settings->maxBookPly) {
    //     if (book->HasPosition(board->ZobristKey)) {
    //         bookMove = book->GetRandomBookMoveWeighted(board->ZobristKey);
    //     }
    // }

    if (bookMove.IsInvalid()) {
        if (settings->useThreading) {
            startThreadedSearch();
        } else {
            startSearch();
        }
    } else {
        search->searchDiagnostics.isBook = true;
        search->searchDiagnostics.moveVal = PGNCreator::NotationFromMove(FenNotation::CurrentFen(board), bookMove);
        settings->diagnostics = search->searchDiagnostics;
        QTimer::singleShot(bookMoveDelayMillis, [=](){ playBookMove(bookMove); });
    }
}

void AIPlayer::startSearch() {
    search->startSearch();
}

void AIPlayer::startThreadedSearch() {
    QThread *thread = QThread::create([this] {
        // Run the search in this thread
        search->startSearch();
        // Quit and clean up this thread after search completes
        QThread::currentThread()->quit();
    });

    // Connect the thread's finished signal to automatically delete the thread
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
    if (!settings->endlessSearchMode) {
        cancelSearchTimer->start(settings->searchTimeMillis);
    }
}

void AIPlayer::timeOutThreadedSearch() {
    if (!cancelSearchTimer->isActive()) {
        search->EndSearch();
    }
}

void AIPlayer::playBookMove(Move bookMove) {
    move = &bookMove;
    moveFound = true;
}

void AIPlayer::onSearchComplete(Move move) {
    cancelSearchTimer->stop();
    *this->move = move;
    moveFound = true;
}
