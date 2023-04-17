
class Visitor;

class Visitable
{
public:
    virtual ~Visitable() = default;
    virtual void accept(Visitor &visitor) = 0;
};