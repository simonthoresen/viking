int query_access(object p)
{
  if(member_array((string)p->query_real_name(),
                  ({"khaine","luke","shauni","knubo","avalon","zabard"})) > -1) return 1;
  return 0;
}

string describe() { return "khaine"; }
