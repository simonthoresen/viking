public int
query_access(object ply) 
{
    return objectp(ply) && wizardp(ply);
}

public string
describe() 
{
    return "artifact_wiz"; 
}
