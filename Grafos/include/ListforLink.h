#ifndef LISTFORLINK_H
#define LISTFORLINK_H

template <typename E>
class ListforLink{
    private:
        void operator =(const ListforLink&) {}
        ListforLink(const ListforLink& obj) {}

    public:
        ListforLink() {}
        virtual ~ListforLink() {}
        virtual void insert(E element, E tag) = 0;
        virtual void append(E element, E tag) = 0;
        virtual E remove() = 0;
        virtual void clear() = 0;
        virtual E getElement() = 0;
        virtual void goToStart() = 0;
        virtual void goToEnd() = 0;
        virtual void goToPos(int pos) = 0;
        virtual void next() = 0;
        virtual bool atEnd() = 0;
        virtual void previous() = 0;
        virtual bool atStart() = 0;
        virtual int getPos() = 0;
        virtual int getSize() = 0;
};

#endif // LISTFORLINK_H
