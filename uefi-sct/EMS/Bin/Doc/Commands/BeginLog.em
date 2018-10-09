Name
BeginLog - Indicate that the logging process begins now.
Usage
BeginLog 
Description
BeginLog will open CaseCategory/CaseName.log and CaseCategory/CaseName.ekl under Log dir,
and append to Summary.log and Summary.ekl under Overall dir.
Notes
It MUST be called only once at the head of the test case.
It MUST be called after CaseLevel, CaseAttribute, CaseVerboseLevel called.
It MUST be called after CaseGuid, CaseName, CaseCategory, CaseDescription called.
It MUST be called before RecordMessage, RecordAssertion, EndLog called.
Example
BeginLog
See also
EndLog