//
// Created by alexg on 12/2/2023.
//
class ABLoopCell: public Cell {
    CellState state;
public:
    ABLoopCell(CellState initial_state): state(initial_state){};

    void flip()
    {
        this->state = (CellState::A == current() ? CellState::B : CellState::A);
    }

    CellState current() const
    {
        return this->state;
    }
};

class ABDeadCell: public Cell {
    CellState state;
public:
    ABDeadCell(CellState initial_state): state(initial_state){};

    void flip()
    {
        this->state = CellState::B;
    }

    CellState current() const
    {
        return this->state;
    }
};

class BADeadCell: public Cell {
    CellState state;
public:
    BADeadCell(CellState initial_state): state(initial_state){};

    void flip()
    {
        this->state = CellState::A;
    }

    CellState current() const
    {
        return this->state;
    }
};


//////////////////////////////////////////////////////
template <typename state_t>
struct LoggerCell : public Cell<state_t> {
    std::ostream& os;
    std::unique_ptr<Cell<state_t>> cell;

    LoggerCell(std::ostream& os, std::unique_ptr<Cell<state_t>> cell) : os(os), cell(std::move(cell)) { }

    void flip() override {
        state_t current_state = cell->current();
        cell->flip();
        state_t new_state = cell->current();
        os << "[" << current_state << " > " << new_state << "]";
    }

    state_t current() const override {
        return cell->current();
    }
};

template <typename state_t>
std::unique_ptr<Cell<state_t>> wrap_into_logger(std::ostream& os, std::unique_ptr<Cell<state_t>> cell) {
    return std::make_unique<LoggerCell<state_t>>(os, std::move(cell));
}
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////
template <typename state_t>
std::unique_ptr<ListPair<state_t» reverse_list(std::unique_ptr<ListPair<state_t» original) {
std::unique_ptr<ListPair<state_t» reversed_list = nullptr;

    while (original) {
    auto current = std::move(original);
    original = std::move(current->next_state);
    current->next_state = std::move(reversed_list);
    reversed_list = std::move(current);
    }

return reversed_list;
}