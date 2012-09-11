namespace abstract
{

template <class I, class H> 
base<I,H>::base(const interface_t* interface, handle_t handle):
    m_interface( interface ), m_handle( handle )
{
}

template <class I, class H> 
base<I,H>::base(const base& origin):
    m_interface( origin.m_interface ), m_handle( (m_interface)? origin.m_interface->copy( origin.m_handle ) : NULL )
{
}

template <class I, class H> 
base<I,H>::~base()
{
if ( !is_null() )
    m_interface->cleanup( m_handle );
m_interface = NULL;
m_handle = NULL;
}

template <class I, class H> 
bool base<I,H>::is_null() const
{
return !interface() || !handle();
}

template <class I, class H> 
const typename base<I,H>::interface_t* base<I,H>::interface() const
{
return m_interface;
}

template <class I, class H> 
typename base<I,H>::handle_t base<I,H>::handle() const
{
return m_handle;
}

template <class I, class H> 
base<I,H>& base<I,H>::operator = (const base& rvalue)
{
m_interface = rvalue.m_interface;
handle_t new_handle = (rvalue.is_null())? NULL : rvalue.m_interface->copy( rvalue.m_handle );

if ( !is_null() )
    m_interface->cleanup( m_handle );
m_handle = new_handle;
return *this;
}

} //namespace abstract

