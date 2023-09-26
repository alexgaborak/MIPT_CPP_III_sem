//
// Created by alexg on 9/16/2023.
//
class DispersionRelationA : public DispersionRelation
{
public:
    double const k;

    DispersionRelationA(double k): k(k) { }

    double operator()(double omega) const override
    {
        return implicit_dispersion_relation_A(omega, k);
    }
};

class DispersionRelationB : public DispersionRelation
{
public:
    double const k, alpha;

    DispersionRelationB(double k, double alpha): k(k), alpha(alpha) { }

    double operator()(double omega) const override
    {
        return implicit_dispersion_relation_B(omega, k, alpha);
    }
};

DispersionRelation const * construct_dispersion_relation_A(double k)
{
    return new DispersionRelationA(k);
}

DispersionRelation const * construct_dispersion_relation_B(double k, double alpha)
{
    return new DispersionRelationB(k, alpha);
}

    call(b);