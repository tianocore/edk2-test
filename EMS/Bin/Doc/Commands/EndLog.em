Name
EndLog - Indicate that the logging process ends now.
Usage
EndLog
Description
EndLog will close CaseCategory/CaseName.log and CaseCategory/CaseName.ekl under Log dir,
and close Summary.log and Summary.ekl under Overall dir.
Notes
It MUST be called only once at the end of the test case.
It MUST be called after BeginLog, RecordMessage, RecordAssertion called.
Example
EndLog
See also
BeginLog