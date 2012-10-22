namespace abstract
{

payload_t::payload_t():
    base()
{
}

payload_t::payload_t(const interface_t* interface, const abstract::core_t& core):
    base( interface, (interface)? interface->init( core.interface(), core.handle() ) : NULL )
{
}

payload_t::~payload_t()
{
}

payload::id_t payload_t::id() const
{
return m_interface->id;
}

} //namespace abstract

