Name
CaseVerboseLevel - Specify the verbost level of the test case.
Usage
CaseVerboseLevel verbostlevel
Description
verbostlevel
    QUIET      : Indicate the verbose level is quiet.
    MINIMAL    : Indicate the verbose level is minimal.
    DEFAULT    : Indicate the verbose level is default.
    NOISY      : Indicate the verbose level is noisy.
    EXHAUSTIVE : Indicate the verbose level is exhaustive.
Notes
It MUST be called before BeginLog called.
Example
CaseVerboseLevel DEFAULT
See also
CaseLevel CaseAttribute