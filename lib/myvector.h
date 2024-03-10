#pragma once

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <utility>


template <typename Ty>
class Vec {
public:
    Vec () = default;
    Vec(const Vec& other) {
        *this = other;
    }
    Vec(std::initializer_list<Ty> init_list) {
        check_capacity(init_list.size());
        size_ = init_list.size();
        for (std::size_t i = 0; i < init_list.size(); ++i) {
            data_[i] = *std::next(init_list.begin(), i);
        }
    }
    explicit Vec(size_t n, Ty val = Ty{}) {
        assign(n, val);
    }
    ~Vec() {
        delete []data_;
    }
    Vec& operator=(const Vec& other) {
        check_capacity(other.size_);
        size_ = other.size_;
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other[i];
        }
        return *this;
    }

    void assign(size_t n, Ty val = Ty{}) {
        check_capacity(n);
        size_ = n;
        for (size_t i = 0; i < n; ++i) {
            data_[i] = val;
        }
    }
    std::size_t size() const {
        return size_;
    }
    void push_back(const Ty& val) {
        check_capacity(size_ + 1);
        data_[size_++] = val;
    }
    bool empty() const {
        return size_ == 0;
    }
    Vec operator[](std::pair<int64_t, int64_t> range) {
        Vec sub(range.second - range.first);
        memcpy(sub.data_, data_ + range.first, sub.size() * sizeof(Ty));
        return sub;
    }
    Ty& operator[](int64_t ind) {
        if (ind >= size_ || -ind > size_) {
            throw std::range_error(
                    std::to_string(ind) + " out of range in vector with size " + std::to_string(size_)
            );
        }
        if (ind < 0) {
            return data_[size_ + ind];
        } else {
            return data_[ind];
        }
    }
    const Ty& operator[](int64_t ind) const {
        if (ind >= size_ || -ind > size_) {
            throw std::range_error(
                    std::to_string(ind) + " out of range in vector with size " + std::to_string(size_)
            );
        }
        if (ind < 0) {
            return data_[size_ + ind];
        } else {
            return data_[ind];
        }
    }
    bool operator==(const Vec<Ty>& other) {
        if (other.size_ != size_) return false;
        for (size_t i = 0; i < size_; ++i) {
            if (other[i] != data_[i]) return false;
        }
        return true;
    }
    Vec operator+ (const Vec<Ty>& other) {
        Vec res(size_ + other.size_);
        for (size_t i = 0; i < size_; ++i) {
            res[i] = data_[i];
        }
        for (size_t i = 0; i < other.size_; ++i) {
            res[i + size_] = other[i];
        }
        return res;
    }
    friend std::ostream& operator<<(std::ostream& out, const Vec& arr) {
        for (const auto& e : arr) out << ' ' << e;
        out << '\n';
        return out;
    }
    friend std::istream& operator>>(std::istream& in, Vec& arr) {
        for (auto& e : arr) in >> e;
        return in;
    }

    Ty* begin() const {
        return data_;
    }
    Ty* end() const {
        return data_ + size_;
    }

private:
    const static int64_t small_buff_size = 32;
    void check_capacity(size_t need) {
        if (need > cap_) {
            size_t new_cap  = 2 * need;
            Ty* new_data = new Ty[new_cap];
            memcpy(new_data, data_, size_ * sizeof(Ty));
            delete[] data_;
            data_ = new_data;
            cap_ = new_cap;
        }
    }

    Ty* data_ = new Ty[small_buff_size];
    int64_t cap_ = small_buff_size;
    int64_t size_ = 0;
};

template <typename Ty>
Ty reversed(Ty cont) {
    std::reverse(std::begin(cont), std::end(cont));
    return cont;
}
