Name
RecordAssertion - Record the assertion to the log file.
Usage
RecordAssertion assertion title description ...
Description
assertion
    PASS : Indicate the result of this assertion is pass.
    WARN : Indicate the result of this assertion is warning.
    FAIL : Indicate the result of this assertion is failure.

RecordAssertion will record the assertion to the log file.
If there are failure assertions in a test case, this case will fail.
Notes
It MUST be called After BeginLog called.
It MUST be called before EndLog called.
Example
RecordAssertion PASS "PxeBaseCode.UdpWrite - Basic Function" Return status is $Status.
See also
RecordMessage