namespace module
{

info_t::info_t(const api_version_t v, const type_t t):
    api_version( v ), type( t )
{
}

info_t::info_t(const module_info_t& info):
    api_version( info.api_version ), type( (module::type_t)info.type )
{
}

} //namespace module

