namespace abstract
{

core_t::core_t():
    base()
{
}

core_t::core_t(const interface_t* interface, handle_t handle):
    base( interface, handle )
{
}

core_t::core_t(const core_t& origin):
    base( origin )
{
}

core_t::~core_t()
{
}

} //namespace abstract

