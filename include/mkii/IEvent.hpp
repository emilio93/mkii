#ifndef MKII_MKII_IEVENT_H
#define MKII_MKII_IEVENT_H

namespace mkii {

/**
 * Interface for an Event.
 */
class IEvent {
 public:
	virtual ~IEvent() {}

	/**
	 * Set up the Event and enable the interruption.
	 */
	virtual void Init(void) = 0;

	/**
	 * Handler for the event.
	 */
	virtual void Handler(void) = 0;

	/**
	 * Cleans up the Event and disable the interruption.
	 */
	virtual void End(void) = 0;
};

}  // namespace mkii

#endif /* MKII_MKII_IEVENT_H */