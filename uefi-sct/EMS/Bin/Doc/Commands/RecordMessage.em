Name
RecordMessage - Record the message to the log file.
Usage
RecordMessage verboselevel message ...
Description
verbostlevel - see CaseVerboseLevel.
    QUIET      : Indicate the current verbose level is quiet.
    MINIMAL    : Indicate the current verbose level is minimal.
    DEFAULT    : Indicate the current verbose level is default.
    NOISY      : Indicate the current verbose level is noisy.
    EXHAUSTIVE : Indicate the current verbose level is exhaustive.

If the current verbostlevel is no higher than the test case verboselevel,
RecordMessage will record the message to the log file, or this message
will be discarded.
Notes
It MUST be called After BeginLog called.
It MUST be called before EndLog called.
Example
RecordMessage DEFAULT The result of the validatepack is $result.
See also
RecordAssertion