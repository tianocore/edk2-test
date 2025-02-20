# UEFI-SCT Project

The UEFI Self-Certification Test (UEFI SCT) is a toolset
for platform developers to validate firmware implementation
compliance to the UEFI Specification from www.uefi.org.
The toolset features a Test Harness for executing
built-in UEFI Compliance Tests, as well as for integrating
user-defined tests that were developed using the
UEFI SCT open source code.

Refer to [UEFI SCT Test Case Specification](https://uefi-sct-testcasespec.readthedocs.io/en/latest/) for detailed information for each assertion in the UEFI SCT fundamental service and protocol tests.
The source of the test case specification is maintained here: [Doc/TestCaseSpec](Doc/TestCaseSpec)

UEFI SCT verifies UEFI Specification version 2.7 (Errata A).
There are tests developed that additionally cover supplementary features. For details, refer to the "New Features" on the [edk2-test Releases](https://github.com/tianocore/edk2-test/releases) page.

Contributions to the UEFI-SCT open source project are covered by the
TianoCore Contribution Agreement 1.1.

The majority of the content in the UEFI-SCT open source project uses a
[BSD 2-Clause License](License.txt).

The files listed in [FILES](FILES)
are covered by additional licenses:[License](License.txt).

The UEFI-SCT is composed of tests that test against UEFI specification.
The maintainers for the test suite
are listed in [Maintainers.txt](Maintainers.txt).

# Resources
* [TianoCore](http://www.tianocore.org)
* [Getting Started with UEFI-SCT](https://github.com/tianocore/tianocore.github.io/wiki/UEFI-SCT)
* [Mailing List](mailto:devel@edk2.groups.io?subject=[edk2-test])
* [UEFI-SCT Issue Tracker](https://github.com/tianocore/edk2-test/issues)
