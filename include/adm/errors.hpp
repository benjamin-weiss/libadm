#pragma once
#include <stdexcept>
#include <adm/elements/audio_object_id.hpp>
#include "adm/libadm_export.h"

namespace adm {
  namespace error {

    class LIBADM_EXPORT AdmException : public std::exception {};

    class LIBADM_EXPORT AudioObjectReferenceCycle : public AdmException {
     public:
      AudioObjectReferenceCycle(AudioObjectId referent, AudioObjectId reference)
          : referent_(referent), reference_(reference) {
        formatMessage();
      }
      AudioObjectId reference() const { return reference_; }
      AudioObjectId referent() const { return referent_; }

      const char* what() const noexcept override { return msg_.c_str(); }

     private:
      void formatMessage();
      AudioObjectId referent_;
      AudioObjectId reference_;
      std::string msg_;
    };

    class LIBADM_EXPORT XmlParsingError : public AdmException {
     public:
      XmlParsingError(const std::string& message, int line)
          : line_(line), msg_(formatMessageWithLine(message)) {}
      XmlParsingError(int line);

      const char* what() const noexcept override { return msg_.c_str(); }

     protected:
      void message(const std::string& message) {
        msg_ = formatMessageWithLine(message);
      }
      int line() const { return line_; }

     private:
      std::string formatMessageWithLine(const std::string& message);

      int line_;
      std::string msg_;
    };

    class LIBADM_EXPORT XmlParsingDuplicateId : public XmlParsingError {
     public:
      XmlParsingDuplicateId(const std::string& id, int line = -1);
    };

  }  // namespace error
}  // namespace adm
