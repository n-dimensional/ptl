namespace abstract
{

transport_t::transport_t():
    base()
{
}

transport_t::transport_t(const interface_t* interface, const abstract::core_t& core):
    base( interface, (interface)? interface->init( core.interface(), core.handle() ) : NULL )
{
}

transport_t::transport_t(const transport_t& origin):
    base( origin )
{
}

transport_t::~transport_t()
{
}

const char* transport_t::full_name() const
{
return m_interface->full_name;
}

const char* transport_t::short_name() const
{
return m_interface->short_name;
}
} //namespace transport_t


