#pragma once
/*
    Iterator （イテレーター、 反復子） は、 振る舞いに関するデザインパターンの一つで、
    リスト、 スタック、 ツリーなどの実際のデータ表現を表に出さずにコレクションの要素を探索することができます。
*/

// イテレータの設計パターン
// 意図: コレクションの要素を公開せずにトラバースできるようにする
// 基礎となる表現 (リスト、スタック、ツリーなど)。
// C++ には、標準ライブラリによって定義されたさまざまなジェネリック コンテナーで
// 動作する iterator の独自の実装があります。
template <typename T, typename U>
class Iterator {
public:
    typedef typename std::vector<T>::iterator iter_type;
    Iterator(U* p_data, bool reverse = false) : m_p_data_(p_data) 
    {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void First() 
    {
        m_it_ = m_p_data_->m_data_.begin();
    }

    void Next() 
    {
        m_it_++;
    }

    bool IsDone() 
    {
        return (m_it_ == m_p_data_->m_data_.end());
    }

    iter_type Current() 
    {
        return m_it_;
    }

private:
    U* m_p_data_;
    iter_type m_it_;
};

// Generic Collections/Containersは、コレクション・クラスと互換性のある新しいイテレータ・インスタンスを
// 取得するための1つ以上のメソッドを提供します。
template <class T>
class Container {
    friend class Iterator<T, Container>;

public:
    void Add(T a) 
    {
        m_data_.push_back(a);
    }

    Iterator<T, Container>* CreateIterator() 
    {
        return new Iterator<T, Container>(this);
    }

private:
    std::vector<T> m_data_;
};

class Data {
public:
    Data(int a = 0) : m_data_(a) {}

    void set_data(int a) 
    {
        m_data_ = a;
    }

    int data() 
    {
        return m_data_;
    }

private:
    int m_data_;
};

// クライアントコードがConcrete IteratorまたはCollectionについて知っている場合と知らない場合があります。
// この実装では、コンテナは汎用であるためintまたはカスタムクラスを使用します。
void ClientCode() {
    std::cout << "________________intを持つイテレータ______________________________________" << std::endl;
    Container<int> cont;

    for (int i = 0; i < 10; i++) {
        cont.Add(i);
    }

    Iterator<int, Container<int>>* it = cont.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next()) {
        std::cout << *it->Current() << std::endl;
    }

    Container<Data> cont2;
    Data a(100), b(1000), c(10000);
    cont2.Add(a);
    cont2.Add(b);
    cont2.Add(c);

    std::cout << "________________カスタムクラスを持つイテレータ______________________________" << std::endl;
    Iterator<Data, Container<Data>>* it2 = cont2.CreateIterator();
    for (it2->First(); !it2->IsDone(); it2->Next()) {
        std::cout << it2->Current()->data() << std::endl;
    }
    delete it;
    delete it2;
}

void Iterator_Start()
{
    ClientCode();
}